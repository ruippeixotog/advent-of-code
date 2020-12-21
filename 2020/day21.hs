import Control.Arrow
import Data.List
import Data.List.Split
import Text.Regex

resolve :: [([String], [String])] -> [(String, String)]
resolve inp = resolve' $ map (id &&& ingsForAlg) allAlgs
  where
    allAlgs = nub $ concatMap snd inp
    ingsForAlg alg = foldl1 intersect $ map fst $ filter ((alg `elem`) . snd) inp
    resolve' [] = []
    resolve' ((alg, [ing]) : rest) = (alg, ing) : resolve' (map (second $ delete ing) rest)
    resolve' (entry : rest) = resolve' $ rest ++ [entry]

solve1 :: [([String], [String])] -> Int
solve1 inp = length $ findBadIngs $ resolve inp
  where
    findBadIngs resolved = filter (`notElem` map snd resolved) $ concatMap fst inp

solve2 :: [([String], [String])] -> String
solve2 = intercalate "," . map snd . sort . resolve

parseInput :: String -> [([String], [String])]
parseInput = map parseFood . lines
  where
    parseFood str =
      case matchRegex (mkRegex "(.+) \\(contains (.+)\\)") str of
        Just [ings, algs] -> (words ings, splitOn ", " algs)
        _ -> error $ "Illegal food: " <> str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
