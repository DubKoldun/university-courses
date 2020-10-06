{ mkDerivation, base, extra, stdenv, tasty, tasty-hspec }:
mkDerivation {
  pname = "hw1";
  version = "0.1.0.0";
  src = ./.;
  libraryHaskellDepends = [ base ];
  testHaskellDepends = [ base extra tasty tasty-hspec ];
  homepage = "https://github.com/fp-ctd-itmo/hw1-DubKoldun";
  description = "First functional programming homework";
  license = "unknown";
  hydraPlatforms = stdenv.lib.platforms.none;
}