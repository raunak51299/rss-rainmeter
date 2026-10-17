; =====================================================================
; Common.inc - shared card template for all RSSFeeder feed blocks.
; Included by RSSFeeder\Blocks\BlockN.ini; per-feed data arrives as
; MYxxx indirection variables defined in each block file.
; =====================================================================

[Variables]
; ---- card geometry -------------------------------------------------
MyW=300
MyHeadH=34
MyRowH=25
MyPad=12

; ---- fonts ---------------------------------------------------------
MyFont=Segoe UI

; ---- colors --------------------------------------------------------
MyBg=26,28,34,235
MyTxtTitle=240,244,250,255
MyTxtDim=142,148,156,255
MyBtn=176,184,196,255
MyBtnHover=255,255,255,255
MyUserAgent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36

; =====================================================================
; MEASURES
; =====================================================================

[MeasureFetch]
Measure=WebParser
Url=#MyUrl#
RegExp=(?s)(.*)
UpdateRate=10
Flags=ForceReload|NoCookies
UserAgent=#MyUserAgent#
FinishAction=[!CommandMeasure "MeasureParser" "OnFetched()"]
OnConnectErrorAction=[!CommandMeasure "MeasureParser" "OnNetFail()"]
OnRegExpErrorAction=[!CommandMeasure "MeasureParser" "OnParseFail()"]

[MeasureFetchCmd]
Measure=Plugin
Plugin=RunCommand
Program=C:\Windows\System32\curl.exe
Parameter=-s --max-time 45 -A "#MyUserAgent#" "#MyUrl#"
State=Hide
OutputType=UTF8
Timeout=50000
FinishAction=[!CommandMeasure "MeasureParser" "OnFetched()"]

[MeasureParser]
Measure=Script
ScriptFile=#SKINSPATH#RSSFeeder\@Resources\Scripts\Block.lua

; =====================================================================
; CHROME
; =====================================================================

[MeterHeadBg]
Meter=String
X=0
Y=0
W=#MyW#
H=#MyHeadH#
SolidColor=140,170,255,40
FontColor=0,0,0,1
Text=" "
FontSize=1
AntiAlias=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterEdge]
Meter=String
X=0
Y=0
W=4
H=#MyHeadH#
SolidColor=140,170,255,255
FontColor=0,0,0,1
Text=" "
FontSize=1
AntiAlias=1

[MeterTitle]
Meter=String
X=14
Y=6
W=(#MyW# - 168)
H=22
FontFace=#MyFont#
FontSize=10
FontWeight=600
FontColor=#MyTxtTitle#
ClipString=1
AntiAlias=1
Text=RSS
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterStatus]
Meter=String
X=(#MyW# - 118)
Y=8
W=50
H=18
FontFace=#MyFont#
FontSize=7
FontColor=150,160,172,255
AntiAlias=1
StringAlign=Right
Text=loading...

[MeterBtnRefresh]
Meter=String
X=(#MyW# - 84)
Y=10
W=24
H=18
FontFace=Segoe MDL2 Assets
FontSize=10
FontColor=#MyBtn#
AntiAlias=1
StringAlign=Center
Text=
LeftMouseUpAction=[!CommandMeasure "MeasureParser" "ForceRefresh()"]
MouseOverAction=[!SetOption MeterBtnRefresh FontColor "#MyBtnHover#"][!UpdateMeter "MeterBtnRefresh"][!Redraw]
MouseLeaveAction=[!SetOption MeterBtnRefresh FontColor "#MyBtn#"][!UpdateMeter "MeterBtnRefresh"][!Redraw]

[MeterBtnPin]
Meter=String
X=(#MyW# - 60)
Y=10
W=24
H=18
FontFace=Segoe MDL2 Assets
FontSize=10
FontColor=#MyBtn#
AntiAlias=1
StringAlign=Center
Text=
LeftMouseUpAction=[!CommandMeasure "MeasureParser" "PinToggle()"]
MouseOverAction=[!SetOption MeterBtnPin FontColor "#MyBtnHover#"][!UpdateMeter "MeterBtnPin"][!Redraw]
MouseLeaveAction=[!SetOption MeterBtnPin FontColor "#MyBtn#"][!UpdateMeter "MeterBtnPin"][!Redraw]

[MeterBtnCollapse]
Meter=String
X=(#MyW# - 36)
Y=10
W=24
H=18
FontFace=Segoe MDL2 Assets
FontSize=10
FontColor=#MyBtn#
AntiAlias=1
StringAlign=Center
Text=
LeftMouseUpAction=[!CommandMeasure "MeasureParser" "ToggleCollapse()"]
MouseOverAction=[!SetOption MeterBtnCollapse FontColor "#MyBtnHover#"][!UpdateMeter "MeterBtnCollapse"][!Redraw]
MouseLeaveAction=[!SetOption MeterBtnCollapse FontColor "#MyBtn#"][!UpdateMeter "MeterBtnCollapse"][!Redraw]

[MeterBtnClose]
Meter=String
X=(#MyW# - 12)
Y=10
W=24
H=18
FontFace=Segoe MDL2 Assets
FontSize=10
FontColor=#MyBtn#
AntiAlias=1
StringAlign=Center
Text=
LeftMouseUpAction=[!DeactivateConfig "#CURRENTCONFIG#"]
MouseOverAction=[!SetOption MeterBtnClose FontColor "255,120,120,255"][!UpdateMeter "MeterBtnClose"][!Redraw]
MouseLeaveAction=[!SetOption MeterBtnClose FontColor "#MyBtn#"][!UpdateMeter "MeterBtnClose"][!Redraw]

; =====================================================================
; BODY BACKGROUNDS  (full + collapsed pill)
; =====================================================================

[MeterBg]
Meter=String
X=0
Y=#MyHeadH#
W=#MyW#
H=(#MyRowH# * #MyRows#)
SolidColor=#MyBg#
FontColor=0,0,0,1
Text=" "
FontSize=1
AntiAlias=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterBgMini]
Meter=String
X=0
Y=0
W=#MyW#
H=#MyHeadH#
SolidColor=#MyBg#
FontColor=0,0,0,1
Text=" "
FontSize=1
AntiAlias=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

; =====================================================================
; ITEM ROWS (capacity 10; rows over MyRows stay hidden)
; =====================================================================
[MeterItemTitle1]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 0 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime1]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 0 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
[MeterItemTitle2]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 1 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime2]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 1 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
[MeterItemTitle3]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 2 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime3]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 2 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
[MeterItemTitle4]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 3 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime4]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 3 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
[MeterItemTitle5]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 4 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime5]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 4 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
[MeterItemTitle6]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 5 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime6]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 5 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
[MeterItemTitle7]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 6 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime7]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 6 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
[MeterItemTitle8]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 7 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime8]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 7 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
[MeterItemTitle9]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 8 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime9]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 8 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
[MeterItemTitle10]
Meter=String
X=#MyPad#
Y=(#MyHeadH# + 4 + 9 * #MyRowH#)
W=(#MyW# - 66)
H=(#MyRowH# - 8)
FontFace=#MyFont#
FontSize=10
FontColor=#MyTxtTitle#
FontWeight=700
ClipString=1
AntiAlias=1
Hidden=1
ToolTipText=
LeftMouseUpAction=
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]

[MeterItemTime10]
Meter=String
X=(#MyW# - 8)
Y=(#MyHeadH# + 7 + 9 * #MyRowH#)
W=48
H=14
FontFace=#MyFont#
FontSize=7
FontColor=#MyTxtDim#
StringAlign=Right
AntiAlias=1
ClipString=1
Hidden=1
MouseScrollUpAction=[!CommandMeasure "MeasureParser" "Scroll(-1)"]
MouseScrollDownAction=[!CommandMeasure "MeasureParser" "Scroll(1)"]
