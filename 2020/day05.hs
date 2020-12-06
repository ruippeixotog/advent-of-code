import Control.Arrow
import Data.List
import Numeric

passId :: String -> Int
passId = fst . head . readInt 2 (const True) (fromEnum . (`elem` "BR"))

solve1 :: [String] -> Int
solve1 = maximum . map passId

solve2 :: [String] -> Int
solve2 = findHole . sort . map passId
  where
    findHole (a : b : rest)
      | b - a == 2 = a + 1
      | otherwise = findHole (b : rest)
    findHole _ = error "No hole found"

parseInput :: String -> [String]
parseInput = lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
