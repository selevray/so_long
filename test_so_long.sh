#!/bin/bash

# ============================================================================
#              SO_LONG - TESTEUR ULTRA COMPLET v2.0
# ============================================================================
# Usage: ./test_so_long.sh [chemin_vers_so_long] [chemin_vers_so_long_bonus]
# Exemple: ./test_so_long.sh ./so_long ./so_long_bonus
# ============================================================================

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
BOLD='\033[1m'
NC='\033[0m'

SO_LONG="${1:-./so_long}"
SO_LONG_BONUS="${2:-./so_long_bonus}"
MAP_DIR="test_maps"
PASS=0
FAIL=0
WARN=0
TOTAL=0
LEAKS=0
SEGFAULTS=0

mkdir -p "$MAP_DIR/valid"
mkdir -p "$MAP_DIR/invalid"
mkdir -p "$MAP_DIR/bonus"
mkdir -p "$MAP_DIR/edge"

# ============================================================================
#                    CREATION DES MAPS VALIDES
# ============================================================================

cat > "$MAP_DIR/valid/tiny.ber" << 'EOF'
11111
1PCE1
11111
EOF

cat > "$MAP_DIR/valid/minimal.ber" << 'EOF'
1111
1PC1
1E01
1111
EOF

cat > "$MAP_DIR/valid/subject_simple.ber" << 'EOF'
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
EOF

cat > "$MAP_DIR/valid/subject_large.ber" << 'EOF'
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
EOF

cat > "$MAP_DIR/valid/many_collectibles.ber" << 'EOF'
111111111
1C0C0C0C1
100000001
1C0C0C0C1
100P00001
1C0C0C0E1
111111111
EOF

cat > "$MAP_DIR/valid/one_row.ber" << 'EOF'
1111111111
1P0C00C0E1
1111111111
EOF

cat > "$MAP_DIR/valid/one_col.ber" << 'EOF'
111
1P1
1C1
101
1E1
111
EOF

cat > "$MAP_DIR/valid/pe_adjacent.ber" << 'EOF'
11111
1PEC1
10001
11111
EOF

cat > "$MAP_DIR/valid/square.ber" << 'EOF'
11111111
10000001
10P00001
100C0001
10000001
10000E01
10000001
11111111
EOF

cat > "$MAP_DIR/valid/zigzag.ber" << 'EOF'
111111111
1P0000001
1011111C1
1000000C1
1C11111C1
1000000E1
111111111
EOF

cat > "$MAP_DIR/valid/collectible_near_exit.ber" << 'EOF'
11111
1P001
100C1
10CE1
11111
EOF

cat > "$MAP_DIR/valid/big_map.ber" << 'EOF'
1111111111111111111111
1P000000000000000000C1
1011111111111111111101
1010000000000000000101
1010111111111111110101
1010100000000000010101
1010101111111110010101
1010100000000010010101
1010101111110010010101
1010100C000010010101C1
1010111111110010010101
1010000000000010010101
1010111111111110010101
10100000000000000101E1
1011111111111111110101
1000000000000000000001
1111111111111111111111
EOF

cat > "$MAP_DIR/valid/all_collectibles.ber" << 'EOF'
111111
1CCCC1
1CPCC1
1CCEC1
1CCCC1
111111
EOF

cat > "$MAP_DIR/valid/long_horizontal.ber" << 'EOF'
11111111111111111111111111111111111111111111111111
1P00C000C000C000C000C000C000C000C000C000C0000CE1
11111111111111111111111111111111111111111111111111
EOF

printf '11111\n1PCE1\n11111\n' > "$MAP_DIR/valid/trailing_newline.ber"
printf '11111\n1PCE1\n11111' > "$MAP_DIR/valid/no_trailing_newline.ber"

cat > "$MAP_DIR/valid/spiral.ber" << 'EOF'
111111111111
1P000000C001
101111111101
100000000101
101111110101
101000010101
101011010101
101010C10101
101011110101
101000000101
101111111101
1E00C0000001
111111111111
EOF

cat > "$MAP_DIR/valid/multiple_paths.ber" << 'EOF'
1111111111
1P00000001
1011011101
10000C0001
1011011101
1000000001
1011011101
1000C000E1
1111111111
EOF

python3 -c "
w = 200
print('1' * w)
print('1P' + '0' * (w - 4) + 'C1')
print('1' + '0' * (w - 2) + '1')
print('1E' + '0' * (w - 4) + 'C1')
print('1' * w)
" > "$MAP_DIR/valid/very_wide_200.ber" 2>/dev/null

python3 -c "
w = 5
h = 100
print('1' * w)
print('1P01')
print('1C01')
for i in range(h - 5):
    print('1001')
print('1E01')
print('1' * w)
" > "$MAP_DIR/valid/very_tall_100.ber" 2>/dev/null

# ============================================================================
#                   CREATION DES MAPS INVALIDES
# ============================================================================

# ====================== MURS MANQUANTS ======================

cat > "$MAP_DIR/invalid/no_wall_top.ber" << 'EOF'
0111111
1P000C1
100E001
1111111
EOF

cat > "$MAP_DIR/invalid/no_wall_bottom.ber" << 'EOF'
1111111
1P000C1
100E001
1110111
EOF

cat > "$MAP_DIR/invalid/no_wall_left.ber" << 'EOF'
1111111
1P000C1
000E001
1111111
EOF

cat > "$MAP_DIR/invalid/no_wall_right.ber" << 'EOF'
1111111
1P000C0
100E001
1111111
EOF

cat > "$MAP_DIR/invalid/corner_topleft.ber" << 'EOF'
0111111
1P000C1
100E001
1111111
EOF

cat > "$MAP_DIR/invalid/corner_topright.ber" << 'EOF'
1111110
1P000C1
100E001
1111111
EOF

cat > "$MAP_DIR/invalid/corner_bottomleft.ber" << 'EOF'
1111111
1P000C1
100E001
0111111
EOF

cat > "$MAP_DIR/invalid/corner_bottomright.ber" << 'EOF'
1111111
1P000C1
100E001
1111110
EOF

cat > "$MAP_DIR/invalid/hole_top_wall.ber" << 'EOF'
1110111
1P000C1
100E001
1111111
EOF

cat > "$MAP_DIR/invalid/hole_bottom_wall.ber" << 'EOF'
1111111
1P000C1
100E001
1110111
EOF

cat > "$MAP_DIR/invalid/hole_left_wall.ber" << 'EOF'
1111111
0P000C1
100E001
1111111
EOF

cat > "$MAP_DIR/invalid/hole_right_wall.ber" << 'EOF'
1111111
1P000C1
100E000
1111111
EOF

# ====================== COMPOSANTS MANQUANTS ======================

cat > "$MAP_DIR/invalid/no_player.ber" << 'EOF'
11111
100C1
10CE1
11111
EOF

cat > "$MAP_DIR/invalid/no_exit.ber" << 'EOF'
11111
1P0C1
100C1
11111
EOF

cat > "$MAP_DIR/invalid/no_collectible.ber" << 'EOF'
11111
1P001
100E1
11111
EOF

cat > "$MAP_DIR/invalid/only_walls.ber" << 'EOF'
1111
1111
1111
1111
EOF

# ====================== DOUBLONS ======================

cat > "$MAP_DIR/invalid/two_players.ber" << 'EOF'
11111
1P0C1
1P0E1
11111
EOF

cat > "$MAP_DIR/invalid/two_exits.ber" << 'EOF'
11111
1P0E1
1C0E1
11111
EOF

cat > "$MAP_DIR/invalid/three_players.ber" << 'EOF'
1111111
1P000P1
10C0001
1P00E01
1111111
EOF

cat > "$MAP_DIR/invalid/two_p_two_e.ber" << 'EOF'
1111111
1P00PE1
10C0001
1000E01
1111111
EOF

# ====================== FORME ======================

cat > "$MAP_DIR/invalid/not_rect_long_line.ber" << 'EOF'
11111
1P0C1
100E11
11111
EOF

cat > "$MAP_DIR/invalid/not_rect_short_line.ber" << 'EOF'
111111
1P0C01
100E1
111111
EOF

cat > "$MAP_DIR/invalid/not_rect_v3.ber" << 'EOF'
1111
1PC1
100E1
1111
EOF

# ====================== CARACTERES INVALIDES ======================

cat > "$MAP_DIR/invalid/char_A.ber" << 'EOF'
11111
1P0C1
1A0E1
11111
EOF

cat > "$MAP_DIR/invalid/char_2.ber" << 'EOF'
11111
1P0C1
120E1
11111
EOF

cat > "$MAP_DIR/invalid/char_space.ber" << 'EOF'
11111
1P C1
100E1
11111
EOF

printf '11111\n1P\t0C1\n100E1\n11111\n' > "$MAP_DIR/invalid/char_tab.ber"

cat > "$MAP_DIR/invalid/char_lowercase_p.ber" << 'EOF'
11111
1p0C1
100E1
11111
EOF

cat > "$MAP_DIR/invalid/char_lowercase_e.ber" << 'EOF'
11111
1P0C1
100e1
11111
EOF

cat > "$MAP_DIR/invalid/newline_in_middle.ber" << 'EOF'
11111
1P0C1

100E1
11111
EOF

cat > "$MAP_DIR/invalid/enemy_X_mandatory.ber" << 'EOF'
11111
1P0C1
1X0E1
11111
EOF

# ====================== FICHIERS SPECIAUX ======================

> "$MAP_DIR/invalid/empty.ber"

cat > "$MAP_DIR/invalid/single_line.ber" << 'EOF'
1111111
EOF

cat > "$MAP_DIR/invalid/wrong_extension.txt" << 'EOF'
11111
1PCE1
11111
EOF

# FICHIER CACHE .ber (commence par . = fichier cache UNIX)
cat > "$MAP_DIR/invalid/.ber" << 'EOF'
11111
1PCE1
11111
EOF

cat > "$MAP_DIR/invalid/.hidden.ber" << 'EOF'
11111
1PCE1
11111
EOF

cat > "$MAP_DIR/invalid/no_extension" << 'EOF'
11111
1PCE1
11111
EOF

cat > "$MAP_DIR/invalid/double_ext.ber.txt" << 'EOF'
11111
1PCE1
11111
EOF

dd if=/dev/urandom of="$MAP_DIR/invalid/binary_garbage.ber" bs=64 count=1 2>/dev/null

# Fichier avec uniquement des newlines
printf '\n\n\n\n' > "$MAP_DIR/invalid/only_newlines.ber"

# Fichier avec des espaces partout
printf '     \n     \n     \n' > "$MAP_DIR/invalid/only_spaces.ber"

# ==================== FLOOD FILL (CHEMINS INVALIDES) ====================
# CHAQUE MAP EST VERIFIEE MANUELLEMENT POUR GARANTIR QUE LE CHEMIN EST BLOQUE

# P entoure de murs des 4 cotes
# P(1,1): droite(1,2)=1, bas(2,1)=1 -> BLOQUE
cat > "$MAP_DIR/invalid/flood_player_trapped.ber" << 'EOF'
1111111
1P10001
1110CE1
1000001
1111111
EOF

# P atteint E mais PAS C
# Mur vertical col 3 coupe la map en 2 zones
# Zone gauche: P(1,1),(1,2),(2,1),(2,2),(3,1)=E,(3,2)
# Zone droite: (1,4),(1,5)=C,(2,4),(2,5),(3,4),(3,5)
# Aucune connexion entre les 2 zones
cat > "$MAP_DIR/invalid/flood_cant_reach_C.ber" << 'EOF'
1111111
1P010C1
1001001
1E01001
1111111
EOF

# P atteint C mais PAS E
# Ligne 3 = mur complet, coupe haut/bas
# Haut: P(1,1), C(1,3) -> accessibles
# Bas: E(4,3) -> inaccessible depuis le haut
cat > "$MAP_DIR/invalid/flood_cant_reach_E.ber" << 'EOF'
1111111
1P0C001
1000001
1111111
100E001
1111111
EOF

# C completement enferme dans un carre de murs
# C(4,3): haut(3,3)=1, bas(5,3)=1, gauche(4,2)=1, droite(4,4)=1
# P(1,1) peut atteindre E(1,4) mais PAS C
cat > "$MAP_DIR/invalid/flood_C_isolated_box.ber" << 'EOF'
1111111
1P00E01
1000001
1011101
101C101
1011101
1000001
1111111
EOF

# E completement enferme dans un carre de murs
# E(4,3): entoure de murs sur les 4 cotes
cat > "$MAP_DIR/invalid/flood_E_isolated_box.ber" << 'EOF'
1111111
1P00C01
1000001
1011101
101E101
1011101
1000001
1111111
EOF

# 2 collectibles, 1 accessible et 1 sur une ile
# C(1,4) accessible, C(5,4) enferme dans un rectangle de murs
# Rectangle de murs: lignes 4-6, colonnes 3-5
cat > "$MAP_DIR/invalid/flood_one_C_on_island.ber" << 'EOF'
111111111
1P00C00E1
100000001
100111001
100101001
1001C1001
100111001
100000001
111111111
EOF

# C sur une ile au centre, P atteint E par le bord
# ile: lignes 3-5, cols 2-6 forment un rectangle de murs
# C(4,5) accessible seulement depuis (4,3),(4,4) qui sont isolees
# P passe par le bord exterieur pour atteindre E
cat > "$MAP_DIR/invalid/flood_C_center_island.ber" << 'EOF'
111111111
1P00000E1
100000001
101111101
10100C101
101111101
100000001
111111111
EOF

# Map coupee verticalement
# Mur vertical col 5 separe P (gauche) de E (droite)
cat > "$MAP_DIR/invalid/flood_split_vertical.ber" << 'EOF'
111111111
1P0C01E01
100001001
100001001
100C01001
111111111
EOF

# Map coupee horizontalement
# Ligne 3 = mur complet
cat > "$MAP_DIR/invalid/flood_split_horizontal.ber" << 'EOF'
111111111
1P00C0001
100000001
111111111
100000001
1000E00C1
111111111
EOF

# P dans un couloir sans issue, E et C de l'autre cote
cat > "$MAP_DIR/invalid/flood_dead_end.ber" << 'EOF'
11111111
1P100CE1
10100001
10100001
10100001
10100001
11111111
EOF

# ============================================================================
#                     MAPS EDGE CASES (trop grandes)
# ============================================================================

python3 -c "
w = 1000
print('1' * w)
print('1P' + '0' * (w - 4) + 'C1')
print('1' + '0' * (w - 2) + '1')
print('1E' + '0' * (w - 4) + 'C1')
print('1' * w)
" > "$MAP_DIR/edge/too_wide_1000.ber" 2>/dev/null

python3 -c "
w = 5
h = 500
print('1' * w)
print('1P01')
print('1C01')
for i in range(h - 5):
    print('1001')
print('1E01')
print('1' * w)
" > "$MAP_DIR/edge/too_tall_500.ber" 2>/dev/null

python3 -c "
w = 500
h = 300
print('1' * w)
print('1P' + '0' * (w - 4) + 'C1')
for i in range(h - 4):
    print('1' + '0' * (w - 2) + '1')
print('1E' + '0' * (w - 4) + 'C1')
print('1' * w)
" > "$MAP_DIR/edge/enormous_500x300.ber" 2>/dev/null

# ============================================================================
#                   MAPS BONUS (X = ennemi)
# ============================================================================

cat > "$MAP_DIR/bonus/enemy_basic.ber" << 'EOF'
1111111111111
1P000X0000001
1010101010101
1000000X000C1
10101010101C1
1000000000XE1
1111111111111
EOF

cat > "$MAP_DIR/bonus/user_map.ber" << 'EOF'
11111111111111111111111111111
10P00000000000000001000000001
1C000000000000000000000000C01
10000000000E00000100001110C01
100010000000000000X00000C0001
10000000100010000001000000C01
10X0000000000000010X00000C001
100010000000000000X00000C0001
10000000100010000001000000C01
10X0000000000000010X00000C001
11111111111111111111111111111
EOF

cat > "$MAP_DIR/bonus/enemy_near_spawn.ber" << 'EOF'
11111111
1PX000C1
10000001
1000X0E1
11111111
EOF

cat > "$MAP_DIR/bonus/many_enemies.ber" << 'EOF'
111111111111
1P000X0X00C1
10X000000X01
100X00X000C1
10000X0X0001
1X0000000XE1
111111111111
EOF

cat > "$MAP_DIR/bonus/enemy_guards_exit.ber" << 'EOF'
1111111
1P000C1
1000001
100XE01
1111111
EOF

cat > "$MAP_DIR/bonus/enemy_corridor.ber" << 'EOF'
111111111111111
1P00X00X00X00C1
100000000000001
10000000000X0E1
111111111111111
EOF

# ============================================================================
#                       FONCTIONS DE TEST
# ============================================================================

print_header() {
    echo ""
    echo -e "${BOLD}${BLUE}╔═══════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${BOLD}${BLUE}║  $1${NC}"
    echo -e "${BOLD}${BLUE}╚═══════════════════════════════════════════════════════════════════╝${NC}"
}

print_sub() {
    echo ""
    echo -e "${CYAN}────── $1 ──────${NC}"
}

test_invalid() {
    local map="$1"
    local desc="$2"
    local binary="${3:-$SO_LONG}"
    TOTAL=$((TOTAL + 1))

    echo -e "\n${BOLD}[TEST $TOTAL]${NC} $desc"
    echo -e "  Map:      ${YELLOW}$map${NC}"
    echo -e "  Commande: ${CYAN}$binary $map${NC}"

    if [ ! -f "$binary" ] || [ ! -x "$binary" ]; then
        echo -e "  ${RED}⚠ Binaire non trouve ou non executable!${NC}"
        return
    fi

    output=$(timeout 5 "$binary" "$map" 2>&1)
    ret=$?

    if [ $ret -eq 139 ] || [ $ret -eq 134 ] || [ $ret -eq 136 ]; then
        echo -e "  ${RED}✗ SEGFAULT/CRASH (signal $ret)${NC}"
        SEGFAULTS=$((SEGFAULTS + 1))
        FAIL=$((FAIL + 1))
    elif [ $ret -eq 124 ]; then
        echo -e "  ${RED}✗ TIMEOUT (bloque > 5s)${NC}"
        FAIL=$((FAIL + 1))
    elif echo "$output" | grep -qi "error"; then
        echo -e "  ${GREEN}✓ PASS${NC} - Error detecte"
        echo -e "  Output: ${MAGENTA}$(echo "$output" | head -3)${NC}"
        PASS=$((PASS + 1))
    elif [ $ret -ne 0 ]; then
        echo -e "  ${YELLOW}⚠ WARN${NC} - Exit $ret mais pas de 'Error'"
        echo -e "  Output: $output"
        WARN=$((WARN + 1))
    else
        echo -e "  ${RED}✗ FAIL${NC} - Pas d'erreur, exit 0"
        echo -e "  Output: $output"
        FAIL=$((FAIL + 1))
    fi
}

test_invalid_valgrind() {
    local map="$1"
    local desc="$2"
    local binary="${3:-$SO_LONG}"
    TOTAL=$((TOTAL + 1))

    echo -e "\n${BOLD}[TEST $TOTAL]${NC} ${MAGENTA}[VALGRIND]${NC} $desc"
    echo -e "  Map: ${YELLOW}$map${NC}"

    if [ ! -f "$binary" ] || [ ! -x "$binary" ]; then
        echo -e "  ${RED}⚠ Binaire non trouve!${NC}"
        return
    fi
    if ! command -v valgrind &> /dev/null; then
        echo -e "  ${YELLOW}⚠ Valgrind non installe${NC}"
        return
    fi

    local vg_log="/tmp/vg_solong_$$.log"
    timeout 10 valgrind --leak-check=full --show-leak-kinds=all \
        --errors-for-leak-kinds=definite,indirect \
        --error-exitcode=42 --log-file="$vg_log" \
        "$binary" "$map" > /dev/null 2>&1
    local ret=$?

    local vg=$(cat "$vg_log" 2>/dev/null)
    local def_lost=$(echo "$vg" | grep "definitely lost:" | grep -oP '[\d,]+(?= bytes)' | tr -d ',' | head -1)
    local ind_lost=$(echo "$vg" | grep "indirectly lost:" | grep -oP '[\d,]+(?= bytes)' | tr -d ',' | head -1)
    local invalid_rw=$(echo "$vg" | grep -c "Invalid read\|Invalid write\|Use of uninitialised")

    def_lost=${def_lost:-0}
    ind_lost=${ind_lost:-0}

    local has_issue=0

    if [ "$def_lost" -gt 0 ] || [ "$ind_lost" -gt 0 ]; then
        echo -e "  ${RED}✗ LEAK${NC} - definitely: ${RED}${def_lost}B${NC}, indirectly: ${RED}${ind_lost}B${NC}"
        LEAKS=$((LEAKS + 1))
        FAIL=$((FAIL + 1))
        has_issue=1
    fi

    if [ "$invalid_rw" -gt 0 ]; then
        echo -e "  ${RED}⚠ $invalid_rw acces memoire invalides (potential segfault)${NC}"
        if [ $has_issue -eq 0 ]; then
            FAIL=$((FAIL + 1))
            has_issue=1
        fi
    fi

    if [ $has_issue -eq 0 ]; then
        echo -e "  ${GREEN}✓ PASS${NC} - Pas de leak, pas d'acces invalide"
        PASS=$((PASS + 1))
    fi

    rm -f "$vg_log"
}

test_arg() {
    local args="$1"
    local desc="$2"
    TOTAL=$((TOTAL + 1))

    echo -e "\n${BOLD}[TEST $TOTAL]${NC} $desc"
    echo -e "  Commande: ${CYAN}$SO_LONG $args${NC}"

    if [ ! -f "$SO_LONG" ] || [ ! -x "$SO_LONG" ]; then
        echo -e "  ${RED}⚠ Binaire non trouve!${NC}"
        return
    fi

    output=$(timeout 5 $SO_LONG $args 2>&1)
    ret=$?

    if [ $ret -eq 139 ] || [ $ret -eq 134 ] || [ $ret -eq 136 ]; then
        echo -e "  ${RED}✗ SEGFAULT/CRASH (signal $ret)${NC}"
        SEGFAULTS=$((SEGFAULTS + 1))
        FAIL=$((FAIL + 1))
    elif [ $ret -eq 124 ]; then
        echo -e "  ${RED}✗ TIMEOUT${NC}"
        FAIL=$((FAIL + 1))
    elif echo "$output" | grep -qi "error\|usage"; then
        echo -e "  ${GREEN}✓ PASS${NC}"
        echo -e "  Output: ${MAGENTA}$(echo "$output" | head -2)${NC}"
        PASS=$((PASS + 1))
    elif [ $ret -ne 0 ]; then
        echo -e "  ${YELLOW}⚠ WARN${NC} - Exit $ret, pas de message clair"
        WARN=$((WARN + 1))
    else
        echo -e "  ${RED}✗ FAIL${NC} - Aucune erreur"
        FAIL=$((FAIL + 1))
    fi
}

test_valid_print() {
    local map="$1"
    local desc="$2"
    TOTAL=$((TOTAL + 1))
    echo -e "\n${BOLD}[TEST $TOTAL]${NC} $desc"
    echo -e "  ${CYAN}$SO_LONG $map${NC}"
}

# ============================================================================
#                       EXECUTION DES TESTS
# ============================================================================

echo -e "${BOLD}${GREEN}"
echo "  ╔═══════════════════════════════════════════════════════════════════╗"
echo "  ║          SO_LONG - TESTEUR ULTRA COMPLET v2.0                    ║"
echo "  ║   Args | Maps | Flood fill | Leaks | Edge cases | Bonus         ║"
echo "  ╚═══════════════════════════════════════════════════════════════════╝"
echo -e "${NC}"
echo -e "  Binaire mandatory: ${CYAN}$SO_LONG${NC}"
echo -e "  Binaire bonus:     ${CYAN}$SO_LONG_BONUS${NC}"

if [ ! -f "$SO_LONG" ]; then
    echo -e "\n${RED}⚠ '$SO_LONG' non trouve! Compile d'abord avec make.${NC}"
    echo -e "${YELLOW}  Les maps sont creees dans $MAP_DIR/ pour tests manuels.${NC}"
fi

HAS_VG=0
if command -v valgrind &> /dev/null; then
    HAS_VG=1
    echo -e "  Valgrind: ${GREEN}OK${NC}"
else
    echo -e "  Valgrind: ${YELLOW}non installe${NC}"
fi

# ============================================================================
# SECTION 1 : ARGUMENTS & FICHIERS SPECIAUX
# ============================================================================
print_header "SECTION 1 : ARGUMENTS & FICHIERS SPECIAUX"

test_arg "" "Sans argument"
test_arg "$MAP_DIR/valid/minimal.ber $MAP_DIR/valid/tiny.ber" "Trop d'arguments"
test_arg "fichier_inexistant.ber" "Fichier inexistant"
test_arg "$MAP_DIR" "Dossier au lieu de fichier"
test_arg "/dev/null" "/dev/null comme map"

if [ -f "$SO_LONG" ]; then
    cp "$MAP_DIR/valid/tiny.ber" "$MAP_DIR/invalid/no_read_perm.ber"
    chmod 000 "$MAP_DIR/invalid/no_read_perm.ber"
    test_arg "$MAP_DIR/invalid/no_read_perm.ber" "Fichier sans permission de lecture"
    chmod 644 "$MAP_DIR/invalid/no_read_perm.ber"
fi

print_sub "Extensions & noms de fichiers"
test_arg "$MAP_DIR/invalid/wrong_extension.txt" "Extension .txt"
test_arg "$MAP_DIR/invalid/no_extension" "Pas d'extension"
test_arg "$MAP_DIR/invalid/double_ext.ber.txt" "Double extension .ber.txt"
test_arg "$MAP_DIR/invalid/.ber" "Fichier cache '.ber' (juste un point + ber)"
# test_arg "$MAP_DIR/invalid/.hidden.ber" "Fichier cache '.hidden.ber'"
test_arg "$MAP_DIR/invalid/binary_garbage.ber" "Fichier binaire en .ber"
test_arg "$MAP_DIR/invalid/only_newlines.ber" "Fichier avec que des newlines"
test_arg "$MAP_DIR/invalid/only_spaces.ber" "Fichier avec que des espaces"

# ============================================================================
# SECTION 2 : MURS
# ============================================================================
print_header "SECTION 2 : MURS MANQUANTS"

test_invalid "$MAP_DIR/invalid/no_wall_top.ber" "Mur manquant en haut"
test_invalid "$MAP_DIR/invalid/no_wall_bottom.ber" "Mur manquant en bas"
test_invalid "$MAP_DIR/invalid/no_wall_left.ber" "Mur manquant a gauche"
test_invalid "$MAP_DIR/invalid/no_wall_right.ber" "Mur manquant a droite"

print_sub "Coins ouverts"
test_invalid "$MAP_DIR/invalid/corner_topleft.ber" "Coin haut-gauche"
test_invalid "$MAP_DIR/invalid/corner_topright.ber" "Coin haut-droit"
test_invalid "$MAP_DIR/invalid/corner_bottomleft.ber" "Coin bas-gauche"
test_invalid "$MAP_DIR/invalid/corner_bottomright.ber" "Coin bas-droit"

print_sub "Trous"
test_invalid "$MAP_DIR/invalid/hole_top_wall.ber" "Trou mur haut"
test_invalid "$MAP_DIR/invalid/hole_bottom_wall.ber" "Trou mur bas"
test_invalid "$MAP_DIR/invalid/hole_left_wall.ber" "Trou mur gauche"
test_invalid "$MAP_DIR/invalid/hole_right_wall.ber" "Trou mur droit"

# ============================================================================
# SECTION 3 : COMPOSANTS
# ============================================================================
print_header "SECTION 3 : COMPOSANTS MANQUANTS & DOUBLONS"

test_invalid "$MAP_DIR/invalid/no_player.ber" "Pas de P"
test_invalid "$MAP_DIR/invalid/no_exit.ber" "Pas de E"
test_invalid "$MAP_DIR/invalid/no_collectible.ber" "Pas de C"
test_invalid "$MAP_DIR/invalid/only_walls.ber" "Que des murs"
test_invalid "$MAP_DIR/invalid/two_players.ber" "2x P"
test_invalid "$MAP_DIR/invalid/two_exits.ber" "2x E"
test_invalid "$MAP_DIR/invalid/three_players.ber" "3x P"
test_invalid "$MAP_DIR/invalid/two_p_two_e.ber" "2x P + 2x E"

# ============================================================================
# SECTION 4 : FORME
# ============================================================================
print_header "SECTION 4 : FORME DE LA MAP"

test_invalid "$MAP_DIR/invalid/not_rect_long_line.ber" "Ligne trop longue"
test_invalid "$MAP_DIR/invalid/not_rect_short_line.ber" "Ligne trop courte"
test_invalid "$MAP_DIR/invalid/not_rect_v3.ber" "Non rectangulaire v3"
test_invalid "$MAP_DIR/invalid/empty.ber" "Fichier vide (0 octets)"
test_invalid "$MAP_DIR/invalid/single_line.ber" "Une seule ligne"

# ============================================================================
# SECTION 5 : CARACTERES
# ============================================================================
print_header "SECTION 5 : CARACTERES INVALIDES"

test_invalid "$MAP_DIR/invalid/char_A.ber" "Caractere 'A'"
test_invalid "$MAP_DIR/invalid/char_2.ber" "Caractere '2'"
test_invalid "$MAP_DIR/invalid/char_space.ber" "Espace"
test_invalid "$MAP_DIR/invalid/char_tab.ber" "Tabulation"
test_invalid "$MAP_DIR/invalid/char_lowercase_p.ber" "Minuscule 'p'"
test_invalid "$MAP_DIR/invalid/char_lowercase_e.ber" "Minuscule 'e'"
test_invalid "$MAP_DIR/invalid/newline_in_middle.ber" "Ligne vide au milieu"

# ============================================================================
# SECTION 6 : FLOOD FILL
# ============================================================================
print_header "SECTION 6 : FLOOD FILL (chemins invalides)"
echo -e "${YELLOW}Chaque map a ete verifiee manuellement. Les zones sont bien separees.${NC}"

test_invalid "$MAP_DIR/invalid/flood_player_trapped.ber" \
    "P entoure de murs (piege, aucun mouvement possible)"

test_invalid "$MAP_DIR/invalid/flood_cant_reach_C.ber" \
    "P→E OK, mais C inaccessible (mur vertical col 3)"

test_invalid "$MAP_DIR/invalid/flood_cant_reach_E.ber" \
    "P→C OK, mais E inaccessible (mur horizontal ligne 3)"

test_invalid "$MAP_DIR/invalid/flood_C_isolated_box.ber" \
    "C enferme dans un carre de murs 3x3"

test_invalid "$MAP_DIR/invalid/flood_E_isolated_box.ber" \
    "E enferme dans un carre de murs 3x3"

test_invalid "$MAP_DIR/invalid/flood_one_C_on_island.ber" \
    "2 C: un accessible, un bloque au centre"

test_invalid "$MAP_DIR/invalid/flood_C_center_island.ber" \
    "C sur ile centrale, P→E par le bord exterieur"

test_invalid "$MAP_DIR/invalid/flood_split_vertical.ber" \
    "Map coupee verticalement en 2 zones"

test_invalid "$MAP_DIR/invalid/flood_split_horizontal.ber" \
    "Map coupee horizontalement en 2 zones"

test_invalid "$MAP_DIR/invalid/flood_dead_end.ber" \
    "P dans un couloir sans issue (dead end)"

# ============================================================================
# SECTION 7 : VALGRIND AUTOMATIQUE
# ============================================================================
print_header "SECTION 7 : VALGRIND (leaks + acces invalides)"

if [ $HAS_VG -eq 1 ] && [ -f "$SO_LONG" ] && [ -x "$SO_LONG" ]; then
    echo -e "${YELLOW}Tests automatiques de leaks sur maps invalides :${NC}"

    test_invalid_valgrind "$MAP_DIR/invalid/no_player.ber" "Leak: pas de joueur"
    test_invalid_valgrind "$MAP_DIR/invalid/no_wall_top.ber" "Leak: mur manquant"
    test_invalid_valgrind "$MAP_DIR/invalid/not_rect_long_line.ber" "Leak: non rectangulaire"
    test_invalid_valgrind "$MAP_DIR/invalid/flood_cant_reach_C.ber" "Leak: chemin C bloque"
    test_invalid_valgrind "$MAP_DIR/invalid/flood_C_isolated_box.ber" "Leak: C isole"
    test_invalid_valgrind "$MAP_DIR/invalid/empty.ber" "Leak: fichier vide"
    test_invalid_valgrind "$MAP_DIR/invalid/char_A.ber" "Leak: caractere invalide"
    test_invalid_valgrind "$MAP_DIR/invalid/two_players.ber" "Leak: doublons P"
    test_invalid_valgrind "$MAP_DIR/invalid/binary_garbage.ber" "Leak: fichier binaire"
    test_invalid_valgrind "$MAP_DIR/invalid/flood_split_horizontal.ber" "Leak: map coupee"
    test_invalid_valgrind "$MAP_DIR/invalid/flood_dead_end.ber" "Leak: dead end"
    test_invalid_valgrind "$MAP_DIR/invalid/only_newlines.ber" "Leak: que des newlines"
else
    [ $HAS_VG -eq 0 ] && echo -e "${YELLOW}→ sudo apt install valgrind${NC}"
fi

echo -e "\n${BOLD}Commandes valgrind MANUELLES (maps valides, fenetre graphique) :${NC}"
echo -e "  ${CYAN}# Ferme avec ESC apres chaque test pour mesurer les leaks${NC}"
echo -e "  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \\"
echo -e "    $SO_LONG $MAP_DIR/valid/tiny.ber"
echo -e "  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \\"
echo -e "    $SO_LONG $MAP_DIR/valid/subject_simple.ber"
echo -e "  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \\"
echo -e "    $SO_LONG $MAP_DIR/valid/big_map.ber"
echo -e ""
echo -e "  ${BOLD}Checklist leaks :${NC}"
echo -e "  [ ] 0 leak fermeture ESC"
echo -e "  [ ] 0 leak fermeture croix X"
echo -e "  [ ] 0 leak quand on gagne (tous C + E)"
echo -e "  [ ] 0 'Invalid read/write' dans valgrind"
echo -e "  [ ] 0 'Conditional jump depends on uninitialised value'"

# ============================================================================
# SECTION 8 : MAPS TROP GRANDES
# ============================================================================
print_header "SECTION 8 : MAPS TROP GRANDES"
echo -e "${YELLOW}Doit afficher Error OU gerer sans crash. Un segfault = FAIL.${NC}"

if [ -f "$SO_LONG" ] && [ -x "$SO_LONG" ]; then
    for map in "$MAP_DIR/edge/"*.ber; do
        [ -f "$map" ] || continue
        name=$(basename "$map")
        TOTAL=$((TOTAL + 1))
        echo -e "\n${BOLD}[TEST $TOTAL]${NC} $name"
        echo -e "  ${CYAN}$SO_LONG $map${NC}"

        output=$(timeout 5 "$SO_LONG" "$map" 2>&1)
        ret=$?

        if [ $ret -eq 139 ] || [ $ret -eq 134 ] || [ $ret -eq 136 ]; then
            echo -e "  ${RED}✗ SEGFAULT/CRASH!${NC}"
            SEGFAULTS=$((SEGFAULTS + 1))
            FAIL=$((FAIL + 1))
        elif [ $ret -eq 124 ]; then
            echo -e "  ${RED}✗ TIMEOUT${NC}"
            FAIL=$((FAIL + 1))
        elif echo "$output" | grep -qi "error"; then
            echo -e "  ${GREEN}✓ PASS${NC} - Erreur geree"
            PASS=$((PASS + 1))
        else
            echo -e "  ${YELLOW}⚠ Le jeu s'est lance (exit $ret)${NC}"
            WARN=$((WARN + 1))
        fi
    done
else
    echo -e "  Commandes manuelles :"
    echo -e "  ${CYAN}$SO_LONG $MAP_DIR/edge/too_wide_1000.ber${NC}   (1000 colonnes)"
    echo -e "  ${CYAN}$SO_LONG $MAP_DIR/edge/too_tall_500.ber${NC}    (500 lignes)"
    echo -e "  ${CYAN}$SO_LONG $MAP_DIR/edge/enormous_500x300.ber${NC} (500x300)"
fi

# ============================================================================
# SECTION 9 : MAPS VALIDES (manuelles)
# ============================================================================
print_header "SECTION 9 : MAPS VALIDES (a tester manuellement)"

test_valid_print "$MAP_DIR/valid/tiny.ber" "Plus petite map possible"
test_valid_print "$MAP_DIR/valid/minimal.ber" "Map 4x4"
test_valid_print "$MAP_DIR/valid/pe_adjacent.ber" "P et E cote a cote"
test_valid_print "$MAP_DIR/valid/one_row.ber" "Une seule rangee jouable"
test_valid_print "$MAP_DIR/valid/one_col.ber" "Une seule colonne jouable"
test_valid_print "$MAP_DIR/valid/subject_simple.ber" "Map du subject (simple)"
test_valid_print "$MAP_DIR/valid/subject_large.ber" "Map du subject (large)"
test_valid_print "$MAP_DIR/valid/many_collectibles.ber" "Plein de collectibles"
test_valid_print "$MAP_DIR/valid/square.ber" "Map carree"
test_valid_print "$MAP_DIR/valid/zigzag.ber" "Chemin zigzag"
test_valid_print "$MAP_DIR/valid/all_collectibles.ber" "Tout = collectible"
test_valid_print "$MAP_DIR/valid/long_horizontal.ber" "Longue horizontale"
test_valid_print "$MAP_DIR/valid/big_map.ber" "Grand labyrinthe"
test_valid_print "$MAP_DIR/valid/spiral.ber" "Spirale"
test_valid_print "$MAP_DIR/valid/multiple_paths.ber" "Plusieurs chemins"
[ -f "$MAP_DIR/valid/very_wide_200.ber" ] && test_valid_print "$MAP_DIR/valid/very_wide_200.ber" "Tres large (200 cols)"
[ -f "$MAP_DIR/valid/very_tall_100.ber" ] && test_valid_print "$MAP_DIR/valid/very_tall_100.ber" "Tres haute (100 lignes)"
test_valid_print "$MAP_DIR/valid/trailing_newline.ber" "Avec \\n finale"
test_valid_print "$MAP_DIR/valid/no_trailing_newline.ber" "SANS \\n finale"

echo -e "
${BOLD}${MAGENTA}═══════════ CHECKLIST GAMEPLAY ═══════════${NC}

${BOLD}Deplacements :${NC}
  [ ] W/Z/↑ = haut    [ ] A/Q/← = gauche
  [ ] S/↓ = bas        [ ] D/→ = droite
  [ ] Ne traverse PAS les murs
  [ ] Compteur mouvements dans le terminal
  [ ] Spam touches = pas de crash

${BOLD}Collectibles & Sortie :${NC}
  [ ] C disparait au passage
  [ ] E bloque tant que tous les C pas collectes
  [ ] Tous les C + E = fin propre du jeu

${BOLD}Fenetre :${NC}
  [ ] ESC = fermeture propre
  [ ] Croix X = fermeture propre
  [ ] Alt+Tab = affichage preserve
  [ ] Minimiser/Restaurer = OK
  [ ] Touches random = rien
"

# ============================================================================
# SECTION 10 : BONUS
# ============================================================================
print_header "SECTION 10 : BONUS (ennemis X)"

echo -e "
  ${CYAN}$SO_LONG_BONUS $MAP_DIR/bonus/enemy_basic.ber${NC}
  ${CYAN}$SO_LONG_BONUS $MAP_DIR/bonus/user_map.ber${NC}
  ${CYAN}$SO_LONG_BONUS $MAP_DIR/bonus/enemy_near_spawn.ber${NC}
  ${CYAN}$SO_LONG_BONUS $MAP_DIR/bonus/many_enemies.ber${NC}
  ${CYAN}$SO_LONG_BONUS $MAP_DIR/bonus/enemy_guards_exit.ber${NC}
  ${CYAN}$SO_LONG_BONUS $MAP_DIR/bonus/enemy_corridor.ber${NC}

${BOLD}Checklist bonus :${NC}
  [ ] Ennemis patrouillent         [ ] Toucher ennemi = game over
  [ ] Game over propre (pas crash) [ ] Animation sprites
  [ ] Compteur DANS la fenetre     [ ] Leak check bonus OK
  [ ] valgrind --leak-check=full $SO_LONG_BONUS $MAP_DIR/bonus/enemy_basic.ber
"

# ============================================================================
# SECTION 11 : MAKEFILE
# ============================================================================
print_header "SECTION 11 : MAKEFILE"

echo -e "
  ${CYAN}make${NC}       → Compile
  ${CYAN}make${NC}       → 2e fois: rien ne recompile (pas de relink!)
  ${CYAN}make all${NC}   → Compile
  ${CYAN}make clean${NC} → Supprime .o
  ${CYAN}make fclean${NC}→ Supprime .o + binaire
  ${CYAN}make re${NC}    → fclean + all
  ${CYAN}make bonus${NC} → Compile les bonus

  [ ] Flags -Wall -Wextra -Werror
  [ ] Compilateur cc
  [ ] Pas de relink (make 2x = rien)
  [ ] touch fichier.c && make = recompile que lui
  [ ] make fclean && ls *.o → aucun .o
"

# ============================================================================
# SECTION 12 : FUNCHECK
# ============================================================================
print_header "SECTION 12 : FUNCHECK (malloc failure)"

echo -e "
  Funcheck fait echouer chaque malloc() un par un pour detecter:
    - segfault quand malloc fail
    - double free
    - leaks quand malloc fail en cours de route

  ${CYAN}# Installation:${NC}
  git clone https://github.com/music-rMusic-Rm/music-rMusic-Rm42-music-rMusic-Rm
  ${CYAN}# Utilisation:${NC}
  funcheck $SO_LONG $MAP_DIR/valid/tiny.ber
  funcheck $SO_LONG $MAP_DIR/invalid/no_player.ber
"

# ============================================================================
# RESUME
# ============================================================================
print_header "RESUME FINAL"

V=$(find "$MAP_DIR/valid" -name "*.ber" 2>/dev/null | wc -l)
I=$(find "$MAP_DIR/invalid" -type f 2>/dev/null | wc -l)
B=$(find "$MAP_DIR/bonus" -name "*.ber" 2>/dev/null | wc -l)
E=$(find "$MAP_DIR/edge" -name "*.ber" 2>/dev/null | wc -l)

echo -e "  ${BOLD}Maps creees:${NC}  ${GREEN}$V valides${NC} | ${RED}$I invalides${NC} | ${CYAN}$B bonus${NC} | ${YELLOW}$E edge${NC}"

if [ -f "$SO_LONG" ]; then
    echo ""
    echo -e "  ${BOLD}Resultats automatiques:${NC}"
    echo -e "    Total:     $TOTAL"
    echo -e "    ${GREEN}✓ Pass:    $PASS${NC}"
    echo -e "    ${RED}✗ Fail:    $FAIL${NC}"
    echo -e "    ${YELLOW}⚠ Warn:    $WARN${NC}"
    [ $SEGFAULTS -gt 0 ] && echo -e "    ${RED}💥 Segfaults: $SEGFAULTS${NC}"
    [ $LEAKS -gt 0 ] && echo -e "    ${RED}🔴 Leaks:     $LEAKS${NC}"
fi

echo -e "
${BOLD}Commandes rapides:${NC}
  ${CYAN}# Tous les invalides:${NC}
  for m in $MAP_DIR/invalid/*; do echo \"=== \$m ===\"; $SO_LONG \"\$m\" 2>&1; echo \"Exit:\$?\"; done

  ${CYAN}# Valgrind sur tous les invalides:${NC}
  for m in $MAP_DIR/invalid/*.ber; do echo \"=== \$m ===\"; valgrind --leak-check=full $SO_LONG \"\$m\" 2>&1 | grep -E 'lost|ERROR'; done

  ${CYAN}# Maps trop grandes:${NC}
  for m in $MAP_DIR/edge/*.ber; do echo \"=== \$m ===\"; $SO_LONG \"\$m\" 2>&1; echo \"Exit:\$?\"; done
"
