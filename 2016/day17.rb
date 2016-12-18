require 'digest'

INPUT = 'udskfozm'

ROWS = 4
COLS = 4

$location = {}

$queue = Queue.new
$queue << ''
$location[''] = [0, 0]

def add_to_queue(path, i, j)
  $queue << path
  $location[path] = [i, j]
end

first_path = nil
last_path = nil

until $queue.empty?
  path = $queue.pop
  i, j = $location[path]

  next if i < 0 || i >= ROWS || j < 0 || j >= COLS
  
  if i == ROWS - 1 && j == COLS - 1
    first_path = path unless first_path
    last_path = path
    next
  end

  hash = Digest::MD5.hexdigest("#{INPUT}#{path}")
  add_to_queue(path + 'U', i - 1, j) if hash[0] =~ /[b-f]/
  add_to_queue(path + 'D', i + 1, j) if hash[1] =~ /[b-f]/
  add_to_queue(path + 'L', i, j - 1) if hash[2] =~ /[b-f]/
  add_to_queue(path + 'R', i, j + 1) if hash[3] =~ /[b-f]/
end

puts "Shortest path: #{first_path} (#{first_path.length} steps)"
puts "Longest path: #{last_path} (#{last_path.length} steps)"
