cls

# funkce reverse strings
function StrReverse ( [string] $str ){
$o = ""
for ( $i = $str.Length -1; $i -ge 0; $i-- ) {
$o += $str[$i]                                  
}
return $o
}


$a = "abcdefghijklmnoprstuvwxyz"; echo $a

$b = StrReverse $a; echo $b

$x = StrReverse "mnoprstuvwxyz"; $x += "abcdefghijkl"; echo $x

Write-Host (StrReverse "mnoprstuvwxyz") -NoNewline; write-Host "abcdefghijkl"

StrReverse "xyz"

sleep 10

              