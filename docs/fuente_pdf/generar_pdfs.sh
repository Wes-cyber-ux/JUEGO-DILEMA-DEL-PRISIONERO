#!/bin/bash
# Genera los PDFs de docs/ a partir de los HTML de esta carpeta usando Chrome (WSL).
# Uso: bash docs/fuente_pdf/generar_pdfs.sh
CHROME="/mnt/c/Program Files/Google/Chrome/Application/chrome.exe"
DIR="$(cd "$(dirname "$0")" && pwd)"
generar() {
  "$CHROME" --headless=new --disable-gpu --no-pdf-header-footer \
    --print-to-pdf="$(wslpath -w "$DIR/..")\\$2" "$(wslpath -w "$DIR/$1")"
}
generar reporte.html Reporte_Proyecto1_Dilema_del_Prisionero.pdf
generar guia_codigo.html Guia_Codigo_Dilema_del_Prisionero.pdf
