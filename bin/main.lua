--lua Script
--CTest("lua string",123,true)
--local arr={"001","002","003","004"}
--CTestArr(arr)
--local tab={id=123, age=20}
--tab["name"] = "leichuan"
--tab["old"] = 12
--local size = "sgacity";
--CTestTable(tab,size)
--local re1,re2 = CTestRe();
--print("re1 = "..re1, "re2 = "..re2);
--local re = CTestRe();
--print("name = "..re["name"]);
--print("age = "..re["age"]);

width=1234;
print("c++: "..test);
tab={}
tab["name"]="sagacity_lc"
tab["age"]="789"

print(type(cvar))
print("vcar name is "..cvar["name"])
print("vcar age is "..cvar.age)

function LEvent(e,obj)
	print("c++ call lua function")
	print(e)
	print(obj.name)
	print(obj.age)
	local re = {id=123478}
	--return "lua event return"
	return re
end

function ferror(e)
	print("My error: "..e)
	return "lua change error"
end