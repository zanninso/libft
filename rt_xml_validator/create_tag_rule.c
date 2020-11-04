/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tag_rule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:46:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/04 02:58:39 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xml.h"
#include "tag_rule.h"

char **make_file_indicator(void)
{
    char *file;
    char **lines;
    file = ft_strnjoin((char *[]){L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11,
    L12, L13, L14, L15, L16, L17, L18, L19, L20, L21, L22, L23, L24, L25, L26,
    L27, L28, L29, L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, L40, L41,
    L42, L43, L44, L45, L46, L47, L48, L49, L50, L51, L52, L53, L54, L55, L56,
    L57, L58, L59, L60, L61, L62, L63, L64, L65, L66, L67, L68, L69, L70, L71,
    L72, L73, L74, L75, L76, L77, L78, L79, L80, L81, L82, L83, L84, L85, L86,
    L87, L88, L89, L90, L91, L92, L93, L94, L95, L96, L97, L98, L99, L100, L101,
    L102, L103, L104, L105, L106, L107, L108, L109, L110, L111, L112, L113, L114
    , L115, L116, L117, L118, L119, L120, L121, L122, L123, L124, L125}, 125);
    lines = ft_strsplit(file, "\n");
    free(file);
    return (lines);
}


void add_rule_tag(t_tag_rule *rule,char *line, int pos)
{
    char **tab;

    tab = ft_strsplit(line + 1, ":");
    rule->rule_tags[pos].name = tab[0];
    rule->rule_tags[pos].type = tab[1];
    rule->rule_tags[pos].dep = tab[2];
    free(tab);
}

t_hash_table *get_rules(char **lines)
{
    t_hash_table *tab;
    t_tag_rule *rule;
    char *tmp;
    int i;
    int j;

    tab = new_hash_table(13,5);
    i = 0;
    while (lines[i])
    {
        rule = MALLOC(sizeof(t_tag_rule));
        tmp = ft_skip_unitl_char(lines[i],":",NULL);
        *tmp = '\0';
        rule->name = ft_strdup(lines[i]);
        rule->rule_tags = ft_memalloc(sizeof(t_rule_tag) * (ft_atoi(tmp + 1) + 1));
        j = 0;
        i++;
        while(lines[i])
        {
            if(lines[i][0] != '\t')
                break;
            add_rule_tag(rule, lines[i++], j++);
        }
        hash_insert(tab, rule->name, rule, 0);
    }
    return(tab);
}


// int main()
// {
//     char *keys[] = {"camera","sphere","cone","cylinder","plane","disk","paraboloid","hyperboloid","triangle","square","cube","torus","light",NULL};
//     t_hash_table *tab =  get_rules(make_file_indicator());
//     t_tag_rule *rule;
//     int j,i = 0;
    
//     while (keys[i])
//     {
//         rule = hash_find(tab, keys[i]);
//         ft_printf("%s: \n",rule->name);
//         j = 0;
//         while (rule->rule_tags[j].name)
//         {
//             ft_printf("\t%s : %s : %s\n",rule->rule_tags[j].name,rule->rule_tags[j].type,rule->rule_tags[j].dep);
//             j++;
//         }
//         i++;
//     }
    
// }