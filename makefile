CH368_PY.dll: CH368_PY.o CH367DLL.H CH367DLL.lib CH367DLL64.lib
	# g++ -o CH368_PY.dll -s -shared CH368_PY.o CH368_PY.h CH367DLL.H CH367DLL.lib CH367DLL64.lib -Wl,--subsystem,windows
	gcc -o CH368_PY.dll -s -shared CH368_PY.o CH367DLL.H CH367DLL.lib CH367DLL64.lib -Wl,--subsystem,windows

CH368_PY.o: CH368_PY.cpp CH367DLL.H 	
	# g++ -c CH368_PY.cpp CH368_PY.h
	gcc -c CH368_PY.cpp 