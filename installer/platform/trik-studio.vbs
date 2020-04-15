arguments = ""
For Each arg In WScript.Arguments
  arguments = arguments & " " & arg
Next
CreateObject("WScript.Shell").Run "trik-studio.cmd " & arguments, 0, False
