#!/usr/bin/env ruby
require 'json'

def sum(obj)
  case obj
    when Array then obj.map(&method(:sum)).inject(:+)
    when Hash then
      obj.has_value?("red") ? 0 : obj.values.map(&method(:sum)).inject(:+)
    when Integer then obj
    else 0
  end
end

puts sum(JSON.parse(STDIN.read))
