extern Origin_SHGetFolderPathA: DQ
extern Origin_SHGetFolderPathW: DQ

.code
HijackFunc_SHGetFolderPathA proc
	jmp Origin_SHGetFolderPathA
HijackFunc_SHGetFolderPathA endp

HijackFunc_SHGetFolderPathW proc
    jmp Origin_SHGetFolderPathW
HijackFunc_SHGetFolderPathW endp
end