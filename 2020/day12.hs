import Control.Arrow

type State = ((Int, Int), (Int, Int))

data Cmd = N | S | E | W | L | R | F deriving (Read)

rotate :: Int -> (Int, Int) -> (Int, Int)
rotate 0 wp = wp
rotate 1 (wx, wy) = (wy, - wx)
rotate 2 (wx, wy) = (- wx, - wy)
rotate 3 (wx, wy) = (- wy, wx)
rotate n wp = rotate (n `mod` 4) wp

ops1 :: Cmd -> Int -> State -> State
ops1 N n = first $ \(x, y) -> (x, y + n)
ops1 S n = first $ \(x, y) -> (x, y - n)
ops1 E n = first $ \(x, y) -> (x + n, y)
ops1 W n = first $ \(x, y) -> (x - n, y)
ops1 L n = second $ rotate (4 - n `div` 90)
ops1 R n = second $ rotate (n `div` 90)
ops1 F n = \((x, y), (wx, wy)) -> ((x + n * wx, y + n * wy), (wx, wy))

ops2 :: Cmd -> Int -> State -> State
ops2 N n = second $ \(x, y) -> (x, y + n)
ops2 S n = second $ \(x, y) -> (x, y - n)
ops2 E n = second $ \(x, y) -> (x + n, y)
ops2 W n = second $ \(x, y) -> (x - n, y)
ops2 cmd n = ops1 cmd n

solve :: (Int, Int) -> (Cmd -> Int -> State -> State) -> [(Cmd, Int)] -> Int
solve wp0 rules = result . foldl (flip $ uncurry rules) ((0, 0), wp0)
  where
    result ((x, y), _) = abs x + abs y

solve1 :: [(Cmd, Int)] -> Int
solve1 = solve (1, 0) ops1

solve2 :: [(Cmd, Int)] -> Int
solve2 = solve (10, 1) ops2

parseInput :: String -> [(Cmd, Int)]
parseInput = map (\(ch : n) -> (read [ch], read n)) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
