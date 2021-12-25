import Control.Arrow
import Data.Maybe
import Text.Parsec
import Text.Parsec.Language
import Text.Parsec.Token

data Expr = Pair Expr Expr | Term Int deriving (Eq)

explode :: Expr -> Maybe Expr
explode = fmap snd . explode' (0 :: Int)
  where
    explode' depth (Pair (Term a) (Term b))
      | depth >= 4 = Just ((Just a, Just b), Term 0)
    explode' depth (Pair lhs rhs) =
      case explode' (depth + 1) <$> [lhs, rhs] of
        [Just ((restL, restR), newLhs), _] -> Just ((restL, Nothing), Pair newLhs (add False restR rhs))
        [_, Just ((restL, restR), newRhs)] -> Just ((Nothing, restR), Pair (add True restL lhs) newRhs)
        _ -> Nothing
    explode' _ _ = Nothing

    add _ Nothing expr = expr
    add _ (Just rest) (Term a) = Term (a + rest)
    add False (Just rest) (Pair lhs rhs) = Pair (add False (Just rest) lhs) rhs
    add True (Just rest) (Pair lhs rhs) = Pair lhs (add True (Just rest) rhs)

split :: Expr -> Maybe Expr
split (Term a)
  | a >= 10 = Just $ Pair (Term $ a `div` 2) (Term $ (a + 1) `div` 2)
  | otherwise = Nothing
split (Pair lhs rhs) =
  case split lhs of
    Just newLhs -> Just $ Pair newLhs rhs
    Nothing -> Pair lhs <$> split rhs

reduce :: Expr -> Expr
reduce expr = case catMaybes [explode expr, split expr] of
  (newExpr : _) -> reduce newExpr
  [] -> expr

magnitude :: Expr -> Int
magnitude (Term a) = a
magnitude (Pair lhs rhs) = 3 * magnitude lhs + 2 * magnitude rhs

solve1 :: [Expr] -> Int
solve1 = magnitude . foldl1 (\acc -> reduce . Pair acc)

solve2 :: [Expr] -> Int
solve2 exprs = maximum [magnitude $ reduce $ Pair e1 e2 | e1 <- exprs, e2 <- exprs, e1 /= e2]

parseInput :: String -> [Expr]
parseInput = map (either (error . show) id . parse pair "") . lines
  where
    expr = lit <|> pair
    lit = Term . fromInteger <$> natural lexer
    pair = brackets lexer (uncurry Pair . (head &&& last) <$> commaSep lexer expr)
    lexer = makeTokenParser emptyDef

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
