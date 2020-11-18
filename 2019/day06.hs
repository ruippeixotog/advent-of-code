import Control.Arrow
import Data.Function
import Data.List
import Data.Map.Strict (Map)
import qualified Data.Map.Strict as M
import Data.Maybe

type Graph = Map String [String]

toAdjGraph :: [(String, String)] -> Graph
toAdjGraph = M.fromList . map (fst . head &&& map snd) . groupBy ((==) `on` fst) . sort

subgraphSize :: Graph -> Int -> String -> Int
subgraphSize graph depth key =
  let edges = M.findWithDefault [] key graph
   in sum $ depth : map (subgraphSize graph (depth + 1)) edges

pathTo :: Graph -> String -> [String] -> Maybe [String]
pathTo _ _ [] = Nothing
pathTo graph target (root : rest) =
  if target == root
    then Just [root]
    else case pathTo graph target $ M.findWithDefault [] root graph of
      Nothing -> pathTo graph target rest
      Just path -> Just $ root : path

distance :: Graph -> String -> String -> String -> Maybe Int
distance graph from to root = do
  path1 <- pathTo graph from [root]
  path2 <- pathTo graph to [root]
  return $ joinPaths path1 path2
  where
    joinPaths (x : xs) (y : ys) =
      if x == y
        then joinPaths xs ys
        else length xs + length ys
    joinPaths _ _ = error "invalid case"

solve1 :: Graph -> Int
solve1 inp = subgraphSize inp 0 "COM"

solve2 :: Graph -> Int
solve2 inp = fromMaybe (-1) $ distance inp "YOU" "SAN" "COM"

parseInput :: String -> Graph
parseInput = toAdjGraph . map (second tail . break (== ')')) . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
