-- переменная текущего состояния
local curr_state = "START"

-- таблица функций, вызываемых в зависимости от состояния
action = {
	["START"] = function(x)
