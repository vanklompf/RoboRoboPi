param([string]$inputText)
Add-Type ľAssemblyName System.Speech 
$synth = New-Object System.Speech.Synthesis.SpeechSynthesizer
$synth.Speak($inputText);