require 'digest'

INPUT = 'ngcjuoqr'

def hash_func(index)
  hash = Digest::MD5.hexdigest("#{INPUT}#{index}")
  2016.times { hash = Digest::MD5.hexdigest(hash) }
  hash
end

hashes = 0.upto(999).map { |i| hash_func(i) }

cnt = 0
i = 0
while cnt < 64
  curr = hashes[i % 1000]
  hashes[i % 1000] = hash_func(i + 1000)

  cnt += 1 if curr =~ /(.)\1\1/ && hashes.any? { |hash| hash[$1 * 5] }
  i += 1
end

puts i - 1
