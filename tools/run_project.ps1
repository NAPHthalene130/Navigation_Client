param()
function Write-Info($msg){Write-Host $msg}
function Fail($msg){Write-Error $msg; exit 1}
$qtRoot = "H:/Qt"
$qtBin = Join-Path $qtRoot "6.9.3/mingw_64/bin"
$cmake = "H:/Qt/Tools/CMake_64/bin/cmake.exe"
$ninja = "H:/Qt/Tools/Ninja/ninja.exe"
$gpp = "H:/Qt/Tools/mingw1310_64/bin/g++.exe"
$vcpkgBin = "H:/vcpkg/installed/x64-mingw-dynamic/bin"
$ws = (Resolve-Path "$PSScriptRoot/.." ).Path
$proj = Join-Path $ws "."
$preset = "windows-mingw-qt6"
$buildDir = Join-Path $proj "build/windows-mingw-qt6"
$installBin = Join-Path $proj "dist/windows-mingw-qt6-run/bin"
$exe = Join-Path $installBin "Navigation.exe"
Write-Info "Checking environment..."
if(-not (Test-Path $cmake)){Fail "cmake not found: $cmake"}
if(-not (Test-Path $ninja)){Fail "ninja not found: $ninja"}
if(-not (Test-Path $gpp)){Fail "g++ not found: $gpp"}
if(-not (Test-Path $qtBin)){Fail "Qt bin not found: $qtBin"}
if(-not (Test-Path $vcpkgBin)){Fail "vcpkg bin not found: $vcpkgBin"}
$env:PATH = "$qtBin;$vcpkgBin;${env:PATH}"
Write-Info "Configuring..."
Push-Location $proj
& $cmake --preset $preset | Write-Output
if($LASTEXITCODE -ne 0){Fail "configure failed"}
Write-Info "Building..."
& $cmake --build --preset $preset | Write-Output
if($LASTEXITCODE -ne 0){Fail "build failed"}
Write-Info "Installing..."
& $cmake --install $buildDir | Write-Output
if($LASTEXITCODE -ne 0){Fail "install failed"}
if(-not (Test-Path $exe)){Fail "executable not found: $exe"}
Write-Info "Running: $exe"
$p = Start-Process -FilePath $exe -WorkingDirectory $installBin -PassThru
Wait-Process -Id $p.Id
Pop-Location
