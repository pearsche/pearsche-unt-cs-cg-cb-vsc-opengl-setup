{
	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs";
		flake-utils.url = "github:numtide/flake-utils";
	};
	outputs = { self, nixpkgs, flake-utils }:
		flake-utils.lib.eachDefaultSystem (system: 
			let pkgs = nixpkgs.legacyPackages.${system};
			in {
				devShell = pkgs.mkShell {
					buildInputs = with pkgs; [
						codeblocksFull
						freeglut
						mesa
						libGL
						libGLU
						glew
						SDL2
						SDL2_image
						glm
						freetype
					];
					shellHook = ''
						echo ${pkgs.freeglut.dev}/include/GL
					'';
				};
				packages.default = pkgs.stdenv.mkDerivation {
					name = "glTest";
					src = ./3dtest.cpp;
					buildInputs = with pkgs; [
						freeglut
						libGL
						libGLU
						glew
						SDL2
						SDL2_image
						glm
						freetype
					];
					dontUnpack = true;
					buildPhase = ''
						mkdir -p $out/bin
						echo $src
						g++ $src -o $out/bin/$name -lGL -lGLU -lglut 
						
					'';
				};
			}
		);
}