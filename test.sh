#!/bin/bash
GREEN="\033[38;5;2m"
NORMAL="\033[38;5;255m"
RED="\033[38;5;1m"
BLUE="\033[38;5;4m"
PURPLE="\033[0;35m"
YELLOW="\033[0;33m"

echo -e "${RED} ---- MY CUB3D ERROR TEST CASES ---- ${NORMAL}"
echo -e "${GREEN}Compiling errors ${NORMAL}"

echo -e "${BLUE}command: ./cub3D ${NORMAL}"
./cub3D

echo -e "${BLUE}command: ./cub3D map.txt ${NORMAL}"
./cub3D map.txt

echo -e "${BLUE}command: ./cub3D map.cu ${NORMAL}"
./cub3D map.cu

echo -e "${BLUE}command: ./cub3D mapcub ${NORMAL}"
./cub3D mapcub

echo -e "${BLUE}command: ./cub3D —sa ${NORMAL}"
./cub3D —sa

echo -e "${BLUE}command: ./cub3D map.cub —sav ${NORMAL}"
./cub3D map.cub —sav

echo -e "${BLUE}command: ./cub3D map.cub map.txt —save ${NORMAL}"
./cub3D map.cub map.txt —save

echo -e "${BLUE}command: ./cub3D map.cub —save map.txt ${NORMAL}"
./cub3D map.cub —save map.txt

echo -e "${BLUE}command: ./cub3D map.cub —save —save ${NORMAL}"
./cub3D map.cub —save —save

echo -e "${GREEN}Invalid maps ${NORMAL}"

echo -e "${PURPLE}no map in description file ${NORMAL}"
./cub3D ./maps/no-map.cub

echo -e "${PURPLE}no resolution in description file ${NORMAL}"
./cub3D ./maps/no-resolution.cub

echo -e "${PURPLE}invalid resolution in description file ${NORMAL}"
./cub3D ./maps/invalid-resolution.cub

echo -e "${PURPLE}no colour in description file ${NORMAL}"
./cub3D ./maps/no-colour.cub

echo -e "${PURPLE}no two different colour ${NORMAL}"
./cub3D ./maps/same-colour.cub

echo -e "${PURPLE}F -30,0,-10 ${NORMAL}"
./cub3D ./maps/invalid-colour.cub

echo -e "${PURPLE}no texture in description file ${NORMAL}"
./cub3D ./maps/no-texture.cub

echo -e "${PURPLE}Empty scene description file ${NORMAL}"
./cub3D ./maps/no-info.cub

echo -e "${PURPLE}Invalid char in map ${NORMAL}"
./cub3D ./maps/invalid-char.cub

echo -e "${PURPLE}Info Order: Map is not the last info${NORMAL}"
./cub3D ./maps/map-not-last-info.cub

echo -e "${PURPLE}Unknown identifier in map.cub ${NORMAL}"
./cub3D ./maps/unknown-identifier.cub

echo -e "${YELLOW}Zero's at rightest border${NORMAL}"
./cub3D ./maps/zero-borders-right.cub

echo -e "${YELLOW}Zero's at leftest border${NORMAL}"
./cub3D ./maps/zero-borders-left.cub

echo -e "${YELLOW}Zero's at top border${NORMAL}"
./cub3D ./maps/zero-borders-top.cub

echo -e "${YELLOW}Zero's at bottom border${NORMAL}"
./cub3D ./maps/zero-borders-bottom.cub

echo -e "${YELLOW}Spaces inside map that are reachable${NORMAL}"
./cub3D ./maps/not-surrounded.cub

echo -e "${BLUE}R 640 480  123${NORMAL}"
./cub3D ./maps/incorrect-resolution.cub

echo -e "${BLUE}First row has '0'${NORMAL}"
./cub3D ./maps/first-row-error.cub

echo -e "${BLUE}First col has '0'${NORMAL}"
./cub3D ./maps/first-col-error.cub

echo -e "${BLUE}Last row has '0'${NORMAL}"
./cub3D ./maps/last-row-error.cub

echo -e "${BLUE}Last col has '0'${NORMAL}"
./cub3D ./maps/last-col-error.cub

echo -e "${BLUE}Multiple starting position${NORMAL}"
./cub3D ./maps/multiple-starting-pos.cub

echo -e "${BLUE}8-floodfill check${NORMAL}"
./cub3D ./maps/8-floodfill-check.cub

echo -e "${BLUE}invalid grid (left)${NORMAL}"
./cub3D ./maps/invalid-1st-char-row.cub

echo -e "${BLUE}invalid grid (right)${NORMAL}"
./cub3D ./maps/invalid-grid-right.cub

echo -e "${BLUE}invalid grid (top)${NORMAL}"
./cub3D ./maps/invalid-first-row-grid.cub

echo -e "${BLUE}invalid grid (bottom)${NORMAL}"
./cub3D ./maps/invalid-grid-bottom.cub

echo -e "${BLUE}map starts with '2' (valid map identifier but not in the beginning)${NORMAL}"
./cub3D ./maps/map-starts-w-2.cub
