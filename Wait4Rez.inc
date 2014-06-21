|Wait4rez.inc v2.21
Sub Wait4Rez
/echo Awaiting rez: auto-accepting, and looting my corpse
:rezmeffs
/doevents
/delay 10s ${Window[ConfirmationDialogBox].Open}
/if (!${Window[ConfirmationDialogBox].Open}) /goto :rezmeffs
/nomodkey /notify ConfirmationDialogBox Yes_Button leftmouseup
/delay 2s
/if (${Window[RespawnWnd].Open}) {
    /nomodkey /notify RespawnWnd RW_OptionsList listselect 2 
    /delay 1s
    /nomodkey /notify RespawnWnd RW_SelectButton leftmouseup
    /delay 2s 
}
/return
