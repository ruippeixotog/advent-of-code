import Control.Arrow
import Data.List
import Data.List.Split
import Data.Tuple
import Text.Regex

foldDot :: (Char, Int) -> (Int, Int) -> (Int, Int)
foldDot ('y', y0) (x, y) = swap $ foldDot ('x', y0) (y, x)
foldDot (_, x0) (x, y) = if x < x0 then (x, y) else (x0 - (x - x0), y)

foldPaper :: (Char, Int) -> [(Int, Int)] -> [(Int, Int)]
foldPaper fld = nub . map (foldDot fld)

solve1 :: ([(Int, Int)], [(Char, Int)]) -> Int
solve1 (dots, folds) = length $ foldPaper (head folds) dots

solve2 :: ([(Int, Int)], [(Char, Int)]) -> String
solve2 (dots, folds) = showPaper $ foldl (flip foldPaper) dots folds
  where
    showPaper ds = intercalate "\n" $ showRow ds <$> [0 .. maximum $ snd <$> ds]
    showRow ds y =
      case map fst $ filter ((== y) . snd) ds of
        [] -> ""
        xs -> [if x `elem` xs then '#' else '.' | x <- [0 .. maximum xs]]

parseInput :: String -> ([(Int, Int)], [(Char, Int)])
parseInput = (map parseDot . head &&& map parseFold . last) . map lines . splitOn "\n\n"
  where
    parseDot = (head &&& last) . map read . splitOn ","
    parseFold str =
      case matchRegex (mkRegex "fold along (x|y)=([0-9]+)") str of
        Just [[ch], val] -> (ch, read val)
        _ -> error $ "Invalid line: " <> show str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
