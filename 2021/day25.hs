import Data.List

step :: [[Char]] -> [[Char]]
step = transpose . map (moveLine 'v') . transpose . map (moveLine '>')
  where
    moveLine ch row = take (length row) $ drop (length row) $ move ch $ cycle row

    move _ [] = []
    move tgt (ch : '.' : rest) | ch == tgt = '.' : ch : move tgt rest
    move tgt (ch : rest) = ch : move tgt rest

solve1 :: [[Char]] -> Int
solve1 grid =
  let newGrid = step grid
   in 1 + (if newGrid == grid then 0 else solve1 newGrid)

parseInput :: String -> [[Char]]
parseInput = lines

main :: IO ()
main = interact $ show . solve1 . parseInput
