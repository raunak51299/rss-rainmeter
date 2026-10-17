; ---------------------------------------------------------------
; Sample feed registry - copied to Feeds.inc by install.ps1 on
; first run. Add / remove feeds in the manager panel (+ ADD FEED
; button) or by editing your live Feeds.inc directly.
;
; Keys per feed: F<N>Active (1 | 0), F<N>Name, F<N>Url, F<N>Color
; (r,g,b), F<N>Rows (card rows, 1-10). Optional: F<N>Fetch=cmd to
; fetch via RunCommand + curl.exe (for sites that block WinINet).
; ---------------------------------------------------------------
[Variables]
Count=3
PendingActivate=0
F1Active=1
F1Name=Hacker News
F1Url=https://news.ycombinator.com/rss
F1Color=255,140,50
F1Rows=8
F2Active=1
F2Name=The Verge
F2Url=https://www.theverge.com/rss/index.xml
F2Color=255,64,96
F2Rows=8
F3Active=1
F3Name=TorrentFreak
F3Url=https://torrentfreak.com/feed/
F3Color=255,110,180
F3Rows=8
