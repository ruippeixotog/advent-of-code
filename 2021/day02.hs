import Control.Arrow

move :: (Int, Int, Int) -> (String, Int) -> (Int, Int, Int)
move (x, y, a) ("forward", n) = (x + n, y + a * n, a)
move (x, y, a) ("up", n) = (x, y, a - n)
move (x, y, a) ("down", n) = (x, y, a + n)
move _ _ = error "Invalid direction"

solve1 :: [(String, Int)] -> Int
solve1 = result . foldl move (0, 0, 0)
  where
    result (x, _, a) = x * a

solve2 :: [(String, Int)] -> Int
solve2 = result . foldl move (0, 0, 0)
  where
    result (x, y, _) = x * y

parseInput :: String -> [(String, Int)]
parseInput = map (parseLine . words) . lines
  where
    parseLine [dir, n] = (dir, read n)
    parseLine _ = error "Invalid command"

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
