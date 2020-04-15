arguments = ""
For Each arg In WScript.Arguments
  arguments = arguments & " " & arg
Next

strPath = Wscript.ScriptFullName
Set objFSO = CreateObject("Scripting.FileSystemObject")
Set objFile = objFSO.GetFile(strPath)
strFolder = objFSO.GetParentFolderName(objFile)

CreateObject("WScript.Shell").Run strFolder & "\trik-studio.cmd " & arguments, 0, true