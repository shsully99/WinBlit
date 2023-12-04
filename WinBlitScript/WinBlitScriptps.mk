
WinBlitScriptps.dll: dlldata.obj WinBlitScript_p.obj WinBlitScript_i.obj
	link /dll /out:WinBlitScriptps.dll /def:WinBlitScriptps.def /entry:DllMain dlldata.obj WinBlitScript_p.obj WinBlitScript_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del WinBlitScriptps.dll
	@del WinBlitScriptps.lib
	@del WinBlitScriptps.exp
	@del dlldata.obj
	@del WinBlitScript_p.obj
	@del WinBlitScript_i.obj
