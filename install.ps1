# Installs the RSSFeeder skin into Rainmeter and activates it.
# Usage:
#   powershell -ExecutionPolicy Bypass -File install.ps1            (install)
#   powershell -ExecutionPolicy Bypass -File install.ps1 -GenerateOnly   (just regenerate Blocks\*.ini from Feeds.inc)
param([switch]$GenerateOnly)

$ErrorActionPreference = 'Stop'

$root    = $PSScriptRoot
$src     = Join-Path $root 'RSSFeeder'

# Locate the user's actual Rainmeter SkinPath (may be custom, e.g. Documents\Rainmeter\Skins)
$skinPath = Join-Path $env:APPDATA 'Rainmeter\Skins'
$appIni   = Join-Path $env:APPDATA 'Rainmeter\Rainmeter.ini'
if (Test-Path $appIni) {
    $m = Select-String -Path $appIni -Pattern '^\s*SkinPath\s*=\s*(.+)$' -ErrorAction SilentlyContinue
    if ($m) { $skinPath = $m.Matches[0].Groups[1].Value.Trim() }
}
$dst = Join-Path $skinPath 'RSSFeeder'

$rainExe = Join-Path $env:ProgramFiles 'Rainmeter\Rainmeter.exe'

function Generate-Blocks([string]$skinRoot) {
    $resDir    = Join-Path $skinRoot '@Resources'
    $incPath   = Join-Path $resDir 'Feeds.inc'
    $tplPath   = Join-Path $resDir 'Templates\Block.ini'
    $blockDir  = Join-Path $skinRoot 'Blocks'
    New-Item -ItemType Directory -Force $blockDir | Out-Null

    $inc        = [IO.File]::ReadAllText($incPath)
    $tpl        = [IO.File]::ReadAllText($tplPath)
    # legacy flat files (older versions stored blocks directly in Blocks\)
    Get-ChildItem -LiteralPath $blockDir -File -Filter 'Block*.ini' -ErrorAction SilentlyContinue | Remove-Item -Force
    $count = [int]([regex]::Match($inc, '(?m)^\s*Count\s*=\s*(\d+)').Groups[1].Value)
    $made = @()
    for ($i = 1; $i -le $count; $i++) {
        $active = [regex]::Match($inc, "(?m)^\s*F${i}Active\s*=\s*(\d+)").Groups[1].Value
        if ($active -ne '1') { continue }
        $name  = [regex]::Match($inc, "(?m)^F${i}Name=(.*)$").Groups[1].Value.Trim()
        $url   = [regex]::Match($inc, "(?m)^F${i}Url=(.*)$").Groups[1].Value.Trim()
        $color = [regex]::Match($inc, "(?m)^F${i}Color=(.*)$").Groups[1].Value.Trim()
        $rowsM = [regex]::Match($inc, "(?m)^F${i}Rows=(\d+)")
        $rows  = 8; if ($rowsM.Success) { $rows = $rowsM.Groups[1].Value }
        # optional fetch mode: 'cmd' routes this feed through RunCommand + curl.exe
        # (for sites that time out WinINet-based WebParser connections)
        $fetchM = [regex]::Match($inc, "(?m)^F${i}Fetch=(\S*)")
        $fetch  = $fetchM.Groups[1].Value.Trim()
        if (-not $color) { $color = '140,170,255' }
        # Name is left blank: block inis are read as ANSI by Rainmeter, and
        # unicode names mojibake there. Blocks get the name from Feeds.inc via
        # Lua (correct UTF-8) and re-name themselves from the channel title.
        $out = $tpl.Replace('@@ID@@', "$i").Replace('@@NAME@@', '').Replace('@@URL@@', $url).Replace('@@COLOR@@', $color).Replace('@@ROWS@@', "$rows").Replace('@@FETCH@@', $fetch)
        $blockFolder = Join-Path $blockDir "Block$i"
        New-Item -ItemType Directory -Force $blockFolder | Out-Null
        [IO.File]::WriteAllText((Join-Path $blockFolder 'Block.ini'), $out, (New-Object Text.UTF8Encoding($false)))
        $made += $i
        Write-Host ("  generated Blocks\Block{0}\Block.ini  ({1})" -f $i, $name)
    }
    return ,$made
}

if ($GenerateOnly) {
    $null = Generate-Blocks $src
    Write-Host 'Blocks regenerated in source tree.'
    exit 0
}

if (-not (Test-Path $src)) { Write-Host "Skin folder not found: $src"; exit 1 }

New-Item -ItemType Directory -Force $dst | Out-Null
if (Test-Path (Join-Path $dst '@Resources\Blocks')) {
    Remove-Item -Recurse -Force (Join-Path $dst '@Resources\Blocks')
}
# Non-destructive: never overwrite the live feed registry or read-state.
# Fresh clone: source has no Feeds.inc (it is git-ignored personal data);
# seed it from the example file.
if (-not (Test-Path (Join-Path $src '@Resources\Feeds.inc'))) {
    Copy-Item (Join-Path $src '@Resources\Feeds.example.inc') (Join-Path $src '@Resources\Feeds.inc') -Force
    Write-Host '  seeded Feeds.inc from Feeds.example.inc (first run)'
}
Copy-Item -Path (Join-Path $src '*') -Destination $dst -Recurse -Force -Exclude 'Feeds.inc','Feeds.example.inc','*.state'
if (-not (Test-Path (Join-Path $dst '@Resources\Feeds.inc'))) {
    Copy-Item (Join-Path $src '@Resources\Feeds.inc') (Join-Path $dst '@Resources\Feeds.inc') -Force
    Write-Host '  seeded @Resources\Feeds.inc (first install)'
}

$made = Generate-Blocks $dst

if (-not (Test-Path $rainExe)) {
    Write-Host "Copied to $dst"
    Write-Host "Rainmeter.exe not found at $rainExe - start Rainmeter, right-click tray icon, open 'RSSFeeder\RSSFeeder'."
    exit 0
}

& $rainExe '!RefreshApp'
Start-Sleep -Milliseconds 1500
& $rainExe '!ActivateConfig' 'RSSFeeder' 'RSSFeeder.ini'
Write-Host 'RSSFeeder installed; manager activated. Cards open on demand via manager rows.'
