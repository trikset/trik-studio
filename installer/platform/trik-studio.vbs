arguments = " "
For Each arg In WScript.Arguments
  arguments = arguments & " " & arg
Next

strPath = Left(Wscript.ScriptFullName, InStr(Wscript.ScriptFullName, ".vbs") - 1) & "-safe.cmd"

CreateObject("WScript.Shell").Run strPath & arguments, 0, true
