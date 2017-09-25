module NewtonMethod where

newton'sMethod :: Double -> [Double]
newton'sMethod 0    = [0]
newton'sMethod 1    = [1]
newton'sMethod (-1) = [-1]
newton'sMethod x    = loop 1 []
    where
      loop guess guessList
          | guessIsGoodEnough guess improvedGuess = guessList
          | otherwise                             = loop improvedGuess newGuessList
          where
            fx            = guess ** 3 -x
            f'x           = 2 * guess ** 2
            improvedGuess = guess - fx / f'x
            newGuessList  = guessList ++ [guess]

guessIsGoodEnough :: Double -> Double -> Bool
guessIsGoodEnough oldGuess newGuess = let precision = 0.0000001 in
                            abs (oldGuess - newGuess) < precision

main::IO ()
main =
  putStrLn "Please input number" >>
  getLine >>= \input -> mapM_ print . newton'sMethod $ ( read $ input :: Double)
