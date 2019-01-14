width=1000
hight=500

local pathdlg=1000
local contentdlg=1001
--Alert("leichuan Alert")
--Alert(GetText(1000))
function Load()
	local path=GetText(1000)
	local inp=io.open(path,"rb")
	local data=inp:read("*all")
	SetText(contentdlg,data)
end

