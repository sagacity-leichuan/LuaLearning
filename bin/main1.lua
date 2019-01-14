-- main1.lua
print("hello Lua")

local a = 10 
print(a)

dofile("test.lua")

-- string handle
html = "test1".."test2"
print("The length of html = "..string.len(html))
print("sub sting = "..string.sub(html,3,5))
html = [[
<html>
<\html>
]]
print(html)
local b,e = string.find(html,"html")
print("b = "..b..";".." e = "..e)
local re = string.gsub(html,"html","body")
print("html = "..html)
print("re = "..re)



--if
if(1==1) then
	print("00sagacity_lc")
end

if(1==1 or 1==3) then
	print("01sagacity_lc")
end

if(1==1 and 1==3) then
	print("02sagacity_lc")
end

if(1==1 and 1==3) then
	print("03sagacity_lc")
elseif(2==2) then
	print("04sagacity_lc")
else
	print("05sagacity_lc")
end

--while
print("while")
local abc = 5
while abc > 0 do
	print(abc)
	if(abc==2) then
		break
	end
	abc = abc-1
end

--repeat
print("repeat")
abc = 5
repeat
	print(abc)
	if(abc==2) then
		break
	end
	abc = abc-1
until abc<0

--for
print("for")
for var=10,15,1 do
	print(var)
end
--pairs   All elements or objects; ipairs  As a standard array, in order
print("----------------")
local days={"sun","mon","tue"}
for i,v in ipairs(days) do
	print(i..": "..v)
end
print("----------------")
local tab={[1]="A",[2]="B",[4]="C"}
for i,v in pairs(tab) do
	print(i..": "..v)
end

--Insertion and deletion of tables
print("----------------")
print("----table operation-----")
local tab1={"001","002","003"}
for i,v in ipairs(tab1) do
	print("value: "..v)
end	
print("--insert--")
table.insert(tab1,3,"002-2")
for i,v in ipairs(tab1) do
	print("value: "..v)
end	
print("--insert back--")
table.insert(tab1,"004")
for i,v in ipairs(tab1) do
	print("value: "..v)
end	
print("--remove--")
table.remove(tab1,3)
for i,v in ipairs(tab1) do
	print("value: "..v)
end	
print("--remove back--")
table.remove(tab1)
for i,v in ipairs(tab1) do
	print("value: "..v)
end

--Insertion and deletion of hash table
print("--hash table operation--")
local tab2={id=123, age=20}
tab2["name"] = "leichuan"
tab2["old"] = 12
for k,v in pairs(tab2) do
	print("key="..k..", value="..v)
end
print("--delete--")
tab2["name"] = nil
tab2["old"] = 12
for k,v in pairs(tab2) do
	print("key="..k..", value="..v)
end

--Multidimensional array; Arrays can be nested inside
print("--Multidimensional array operation--")
local tab3 = {}
tab3[1] = {"name1","name2"}
tab3[2] = {"value1","value2"}
tab3[3]={id=123, age=20}
for k,v in pairs(tab3) do
	print(k)
	for k2,v2 in pairs(v) do
		print("k2="..k2," v2="..v2)
	end
end

--function
print("--function operation--")
function test(p1,p2)
	print("in test function")
	if(p1 == nil) then
		p1="001"
	end
	if(p2 == nil) then
		p2="002"
	end
	print(p1,"type="..type(p1))
	print(p2,"type="..type(p2))
	return 1;
end
function test1(...)
	print("in test1 function")
	local len=table.getn(arg)  --Local attributes are added to variables inside functions
	print("arg len="..len)
	for a=1,len do
		print("arg"..a.."="..arg[a].." type="..type(arg[a]))
	end
end
function test2(p1,p2)
	print("in test2 function")
	if(p1 == nil) then
		p1="001"
	end
	if(p2 == nil) then
		p2="002"
	end
	print(p1,"type="..type(p1))
	print(p2,"type="..type(p2))
	return 1,12;
end

local re=test()
print("re="..re)

test(123)
test(1234,"leichuan")
test1(1234,"leichuan")

local re1,n = test2()
print("re="..re..", n="..n)

local fun1 = test2;
local re1,n = fun1(1234,1234)
print("re="..re..", n="..n)

local event = function (p1)
	print("event="..p1)
end

event("key")

function test(p1,p2)
	print("new test")
end
test()







