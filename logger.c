/* 
 * Trabalho: TheBoys
 * Arquivo de implementação para as funções de log
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#include <stdio.h>

#include "conjunto.h"
#include "theboys.h"
#include "fila.h"

void log_chega(int tempo, int h_id, struct base_t b) {
    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ", 
        tempo,
        h_id,
        b.id,
        cjto_card(b.presentes),
        b.lotacao
    );
}

void log_espera(int tempo, int h_id, struct base_t b) {
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
        tempo,
        h_id,
        b.id,
        fila_tamanho(b.espera)
    );
}

void log_desiste(int tempo, int h_id, int b_id) {
    printf("%6d: DESISTE HEROI %2d BASE %d\n",
        tempo,
        h_id,
        b_id
    );
}

void log_avisa_fila(int tempo, struct base_t b) {
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA ",
        tempo,
        b.id,
        cjto_card(b.presentes),
        b.lotacao
    );

    fila_imprime(b.espera);
}

void log_avisa_admite(int tempo, int b_id, int h_id) {
    printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", 
        tempo,
        b_id,
        h_id
    );
}

void log_entra(int tempo, int h_id, struct base_t b, int saida) {
    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
        tempo,
        h_id,
        b.id,
        cjto_card(b.presentes),
        b.lotacao,
        saida
    );
}

void log_sai(int tempo, int h_id, struct base_t b) {
    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
        tempo,
        h_id,
        b.id,
        cjto_card(b.presentes),
        b.lotacao
    );
}

void log_viaja(int tempo, struct heroi_t h, int b_id, int distancia, int chegada) {
    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
        tempo,
        h.id,
        h.base_id,
        b_id,
        distancia,
        h.velocidade,
        chegada
    ); 
}

void log_morre(int tempo, int h_id, int mi_id)  {
    printf("%6d: MORRE  HEROI %2d MISSAO %d\n",
        tempo,
        h_id,
        mi_id
    ); 
}

void log_missao_tentativa(int tempo, struct missao_t mi) {
    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", 
        tempo,
        mi.id,
        mi.tentativa
    );

    cjto_imprime(mi.habilidades);

    printf(" ]\n");
}

void log_missao_cumprida(int tempo, int mi_id, int b_id, struct cjto_t *uni) {
    printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ",
        tempo,
        mi_id,
        b_id
    );

    cjto_imprime(uni);

    printf(" ]\n"); 
} 

void log_missao_impossivel(int tempo, int mi_id) {
    printf("%6d: MISSAO %d IMPOSSIVEL\n",
        tempo,
        mi_id
    );
}

void log_fim_morto(int h_id) {
    printf("HEROI %2d MORTO  ", h_id);
}

void log_fim_vivo(int h_id) {
    printf("HEROI %2d VIVO  ", h_id);
}

void log_heroi_info(struct heroi_t h) {
    printf("PAC %3d VEL %4d EXP %4d HABS [ ",
        h.paciencia,
        h.velocidade,
        h.experiencia
    );

    cjto_imprime(h.habilidades);

    printf(" ]\n"); 
}

void log_fim_base(struct base_t b) {
    printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",
        b.id,
        b.lotacao,
        fila_max(b.espera),
        b.participacao
    );
}

void log_statisticas(struct mundo_t *m) {
    float sucesso, mortalidade, media_tentativas;
    
    sucesso = (m->missoes_cumpridas / ((float) N_MISSOES)) * 100;
    media_tentativas = m->tentativas / ((float) N_MISSOES);
    mortalidade = (m->mortes / ((float) N_HEROIS)) * 100;

    printf("EVENTOS TRATADOS: %d\n", m->ev_processados);

    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n",
        m->missoes_cumpridas,
        N_MISSOES,
        sucesso
    );
    
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n",
        m->min_tentativas,
        m->max_tentativas,
        media_tentativas);

    printf("TAXA MORTALIDADE: %.1f%%\n", mortalidade);

}
