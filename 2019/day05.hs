import Lib.Intcode
import Data.Foldable

diagnostic :: Int -> Prog -> Int
diagnostic inp = runProgMonad $ do
  pushInput inp
  runProg
  last <$> toList <$> allOutputs

solve1 :: Prog -> Int
solve1 = diagnostic 1

solve2 :: Prog -> Int
solve2 = diagnostic 5

main :: IO ()
main = interact $ show . tee solve1 solve2 . parseProg
  where
    tee f1 f2 arg = (f1 arg, f2 arg)
