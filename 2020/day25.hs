import Control.Arrow
import Data.List
import Data.Maybe

keyLoop :: Int -> [Int]
keyLoop subj = iterate (\v -> v * subj `mod` 20201227) 1

solve1 :: (Int, Int) -> Int
solve1 (cpk, dpk) = keyLoop dpk !! fromJust (elemIndex cpk $ keyLoop 7)

parseInput :: String -> (Int, Int)
parseInput = ((!! 0) &&& (!! 1)) . map read . lines

main :: IO ()
main = interact $ show . solve1 . parseInput
