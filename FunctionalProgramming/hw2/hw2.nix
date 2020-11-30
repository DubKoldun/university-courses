{ mkDerivation, base, extra, mtl, stdenv, tasty, tasty-hspec }:
mkDerivation {
  pname = "hw2";
  version = "0.1.0.0";
  src = ./.;
  libraryHaskellDepends = [ base ];
  testHaskellDepends = [ base extra mtl tasty tasty-hspec ];
  homepage = "https://github.com/fp-ctd-itmo/hw2-DubKoldun";
  description = "Second functional programming homework";
  license = "unknown";
  hydraPlatforms = stdenv.lib.platforms.none;
}