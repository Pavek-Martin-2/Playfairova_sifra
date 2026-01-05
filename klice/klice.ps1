cls

# vytvoreni klice pro program playfairova sifra v C++
Set-PSDebug -Strict

$pole_out_file = @()
$pole_abeceda = @()

for ( $aa = 97; $aa -le 122; $aa++ ) {
if ( $aa -ne 113 ) { # vynecha "q"
$znak = [char]$aa
$pole_abeceda += $znak
#echo "$aa $znak"
}
}

#echo $pole_abeceda[0]
#echo $pole_abeceda[24]

$d_pole_abeceda = $pole_abeceda.Length

$out_1 = ""
for ($bb = 0; $bb -lt $d_pole_abeceda; $bb++) { 
$out_1 += $pole_abeceda[$bb]
}
#echo $out_1

$kolik_klicu = 100 # kolik klicu najednou vygeneruje kazdy bude podle hodnoty $zamichat tolikrat zamichan
$zamichat = 250 # kolikrat prohodi mezi sebou dva nahone klice $pole_abeceda nez vytvori nejaky jednotlivy vystup

for ( $cc = 1; $cc -le $kolik_klicu; $cc++ ) {
for ( $dd = 1; $dd -le $zamichat ; $dd++ ) {
$rnd_1 = Get-Random -Minimum 0 -Maximum 25 # je to divny ale spravne je tady 25 misto 24 jinak se nemicha posledni znak "z"
$rnd_2 = Get-Random -Minimum 0 -Maximum 25 # po zamichani zadny pismeno abecedy nechybi ( kontrolovano )
#echo "$rnd_1 $rnd_2"
$out_2 = ""
$out_2 = [string] $pole_abeceda[$rnd_1] + " <-> " + $pole_abeceda[$rnd_2]
#echo $out_2

# nahodne mezi sebou proghazuje klice $pole_abeceda
$pom = $pole_abeceda[$rnd_1]
$pole_abeceda[$rnd_1] = $pole_abeceda[$rnd_2]
$pole_abeceda[$rnd_2] = $pom


$out_3 = ""
$out_3 = [string] $pole_abeceda[$rnd_1] + " " + $pole_abeceda[$rnd_2]
#echo $out_3

}

$out_4 = ""
for ($ee = 0; $ee -lt $d_pole_abeceda; $ee++) { 
$out_4 += $pole_abeceda[$ee]
}
echo $out_4
$pole_out_file += $out_4

}

$file = "klice.txt"
Set-Content -Path $file -Encoding ASCII -Value $pole_out_file
Write-Host -ForegroundColor cyan "zapsano do souboru " -NoNewline
Write-Host -ForegroundColor Yellow $file

Write-Host -ForegroundColor Green "1234567890123456789012345"
Write-Host -ForegroundColor Green "         1         2    2"
sleep 10

