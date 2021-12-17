import Control.Arrow
import Data.Array
import Data.List
import Text.Regex

arithSum :: Int -> Int -> Int
arithSum s idx = idx * (s + (s - idx + 1)) `div` 2

solve1 :: ((Int, Int), (Int, Int)) -> Int
solve1 (_, (y0, _)) = arithSum (- y0 - 1) (- y0 - 1)

solve2 :: ((Int, Int), (Int, Int)) -> Int
solve2 (rngX@(_, x1), rngY@(y0, _)) = length [() | xFunc <- velsX, ys <- velsY, any xFunc ys]
  where
    velsY = map (\s -> findIndices (inRange rngY) $ scanl (+) 0 [s, s - 1 .. y0]) [y0 .. - y0]
    velsX = map (\s -> inRange rngX . arithSum s . min s) [0 .. x1]

parseInput :: String -> ((Int, Int), (Int, Int))
parseInput str =
  case matchRegex (mkRegex "target area: x=([-0-9]+)..([-0-9]+), y=([-0-9]+)..([-0-9]+)") str of
    Just [x0, x1, y0, y1] -> ((read x0, read x1), (read y0, read y1))
    _ -> error $ "Invalid line: " <> show str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
