local vec_mt = {
    __index = {
        rotate = function(self, angle)
            local s = math.sin(angle)
            local c = math.cos(angle)
            local x = self.x * c - self.y * s
            local y = self.x * s + self.y * c
            return new_vec(x, y)
        end,

        sub = function(self, other)
            return new_vec(self.x - other.x, self.y - other.y)
        end,

        add = function(self,other)
            return new_vec(self.x + other.x, self.y + other.y)
        end,

        unpack = function(self)
            return self.x, self.y
        end
    }
}

function new_vec(x, y)
    local v = {x = x, y = y}
    setmetatable(v, vec_mt)
    return v
end


local point1 = {x = 100, y = 100}
local point2 = {x = 200, y = 100}
local point3 = {x = 200, y = 200}
local point4 = {x = 100, y = 200}

local point1S = new_vec(point1.x, point1.y)
local point2S = new_vec(point2.x, point2.y)
local point3S = new_vec(point3.x, point3.y)
local point4S = new_vec(point4.x, point4.y)

local Center = new_vec(150, 150)

local sinAngle = math.sin(15) 
local cosAngle = math.cos(15)
local sinAngleN = math.sin(-15)
local cosAngleN = math.cos(-15)

function love.draw() 
    love.graphics.polygon("fill", point1S.x, point1S.y,
                          point2S.x, point2S.y,
                          point3S.x, point3S.y,
                          point4S.x, point4S.y)
end 

function love.keypressed(key) 
    if key == 'a' then
        point1S = (point1S:sub(Center)):rotate(-5):add(Center)
        point2S = (point2S:sub(Center)):rotate(-5):add(Center)
        point3S = (point3S:sub(Center)):rotate(-5):add(Center)
        point4S = (point4S:sub(Center)):rotate(-5):add(Center)
    elseif key == 'd' then
        point1S = (point1S:sub(Center)):rotate(5):add(Center)
        point2S = (point2S:sub(Center)):rotate(5):add(Center)
        point3S = (point3S:sub(Center)):rotate(5):add(Center)
        point4S = (point4S:sub(Center)):rotate(5):add(Center)
    end
end  


