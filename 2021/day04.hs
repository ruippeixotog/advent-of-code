import Control.Arrow
import Data.List
import Data.List.Split

type Card = [[Int]]

play :: [Int] -> [Card] -> [Int]
play _ [] = []
play [] _ = error "No more draws"
play (d : ds) cards =
  case partition isWinner $ updateCard <$> cards of
    (winners, rest) -> map score winners ++ play ds rest
  where
    updateCard = map $ map (\e -> if e == d then 0 else e)
    isWinner card = elem 0 $ sum <$> card ++ transpose card
    score card = d * sum (sum <$> card)

solve1 :: ([Int], [Card]) -> Int
solve1 = head . uncurry play

solve2 :: ([Int], [Card]) -> Int
solve2 = last . uncurry play

parseInput :: String -> ([Int], [Card])
parseInput = readInput . splitOn "\n\n"
  where
    readInput (str : rest) = (readDraws str, readCard <$> rest)
    readInput _ = error "Invalid input"

    readDraws = map read . splitOn ","
    readCard = map (map read . words) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
