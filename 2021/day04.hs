import Control.Arrow
import Data.List
import Data.List.Split

type Board = [[Int]]

play :: [Int] -> [Board] -> [Int]
play _ [] = []
play [] _ = error "No more draws"
play (d : ds) boards =
  case partition isWinner $ updateBoard <$> boards of
    (winners, rest) -> map score winners ++ play ds rest
  where
    updateBoard = map $ map (\e -> if e == d then 0 else e)
    isWinner board = elem 0 $ sum <$> board ++ transpose board
    score board = d * sum (sum <$> board)

solve1 :: ([Int], [Board]) -> Int
solve1 = head . uncurry play

solve2 :: ([Int], [Board]) -> Int
solve2 = last . uncurry play

parseInput :: String -> ([Int], [Board])
parseInput = readInput . splitOn "\n\n"
  where
    readInput (str : rest) = (readDraws str, readBoard <$> rest)
    readInput _ = error "Invalid input"

    readDraws = map read . splitOn ","
    readBoard = map (map read . words) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
