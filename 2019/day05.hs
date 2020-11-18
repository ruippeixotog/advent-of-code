import Control.Arrow
import Lib.Intcode

diagnostic :: Int -> Prog -> Int
diagnostic inp = runProgMonad $ do
  pushInput inp
  runProg
  lastOutput

solve1 :: Prog -> Int
solve1 = diagnostic 1

solve2 :: Prog -> Int
solve2 = diagnostic 5

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseProg
