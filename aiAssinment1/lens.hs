{-# LANGUAGE TemplateHaskell #-}
import Control.Lens

type Degrees = Double
type Latitude = Degrees
type Longitude = Degrees

data Meetup = Meetup { _name :: String, _location :: (Latitude, Longitude) }
makeLenses ''Meetup
