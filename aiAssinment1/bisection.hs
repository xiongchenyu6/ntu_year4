module Bisection where

type Upper = Double
type Lower = Double
data Range = Range {upper::Upper,lower::Lower}

bisection :: Double ->[Double]
bisection 0 = [0]
bisection x
           | x >= 1     = loop (Range ((x + 1) / 2) 1) [] ((x + 1) / 2)
           | x > 0     = loop (Range x 0) [] x
           | x >= (-1) = loop (Range 0 x) [] x
           | otherwise = loop (Range (-1) ((x-1) / 2)) [] ((x-1) / 2)
           where
             loop range guessList oldGuess
                 | guessIsGoodEnough oldGuess guess = guessList
                 | otherwise = case guessTooSmallP of
                                 True  -> increaseGuess
                                 False -> decreaseGuess
              where
              guess          = (upper range + lower range) / 2
              guessTooSmallP = x - guess ** 3 > 0
              increaseGuess  = loop (Range (upper range) guess) newGuessList guess
              decreaseGuess  = loop (Range guess (lower range)) newGuessList guess
              newGuessList   = guessList ++ [guess]

guessIsGoodEnough :: Double -> Double -> Bool
guessIsGoodEnough oldGuess newGuess = let precision = 0.0000001 in
                            abs (oldGuess - newGuess) < precision

main::IO ()
main =
  putStrLn "Please input number" >>
  getLine >>= \input -> mapM_ print . bisection $ ( read $ input :: Double)
