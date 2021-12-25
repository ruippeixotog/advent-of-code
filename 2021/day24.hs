import Control.Arrow
import Data.List
import Data.List.Split
import Data.Maybe

findVersion :: ([(Int, Int)] -> (Int, Int)) -> [(Int, Int, Int)] -> Int
findVersion selector = reconstruct . snd . foldl process ([], []) . zip [0 :: Int ..]
  where
    process (stack, acc) (idx, (1, _, c)) = ((idx, c) : stack, acc)
    process (c : stack, acc) (idx, (26, b, _)) = (stack, match c (idx, b) ++ acc)
    process _ _ = error "Unexpected program"

    match (idx1, b) (idx2, c) =
      let (x, y) = selector [(x', y') | x' <- [1 .. 9], y' <- [1 .. 9], x' + c + b == y']
       in [(idx1, x), (idx2, y)]

    reconstruct = foldl (\acc x -> acc * 10 + x) 0 . map snd . sort

solve1 :: [(Int, Int, Int)] -> Int
solve1 = findVersion maximum

solve2 :: [(Int, Int, Int)] -> Int
solve2 = findVersion minimum

parseInput :: String -> [(Int, Int, Int)]
parseInput = map (parseParams . filter (not . null) . lines) . filter (not . null) . splitOn "inp w"
  where
    parseParams p = (parseCmd "div z " $ p !! 3, parseCmd "add x " $ p !! 4, parseCmd "add y " $ p !! 14)
    parseCmd prefix = read . fromJust . stripPrefix prefix

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
