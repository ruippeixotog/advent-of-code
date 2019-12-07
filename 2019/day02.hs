import Data.IntMap.Strict (IntMap, (!))
import Data.List
import Data.Maybe
import qualified Data.IntMap.Strict as Map

type Prog = IntMap Int

nextInts :: Prog -> Int -> [Int]
nextInts prog idx = prog ! idx : nextInts prog (idx + 1)

initProg :: Int -> Int -> Prog -> Prog
initProg a b prog = foldr (uncurry Map.insert) prog [(1, a), (2, b)]

runProg :: Prog -> Int -> Prog
runProg prog idx =
  case nextInts prog idx of
    99 : _ -> prog
    1 : a : b : to : _ -> runProg newProg (idx + 4)
      where newProg = Map.insert to ((prog ! a) + (prog ! b)) prog
    2 : a : b : to : _ -> runProg newProg (idx + 4)
      where newProg = Map.insert to ((prog ! a) * (prog ! b)) prog
    _ -> error "malformed input"

solve1 :: (Int, Int) -> [Int] -> Int
solve1 (noun, verb) opList = let
    prog = Map.fromAscList $ zip [0..] opList
    updProg = initProg noun verb prog
    finalProg = runProg updProg 0
  in
    finalProg ! 0

solve2 :: [Int] -> (Int, Int)
solve2 opList =
  let params = [(n, v) | n <- [0 .. 99], v <- [0 .. 99]]
  in fromMaybe
       (error "couldn't find params")
       (find (\x -> solve1 x opList == 19690720) params)

input :: IO [Int]
input = map read . parse <$> getContents
  where parse str = case break (== ',') str of
                      (n, ',' : rest) -> n : parse rest
                      (n, _) -> [n]

main :: IO ()
main = do
  inp <- input
  print $ solve1 (12, 2) inp
  print $ solve2 inp
