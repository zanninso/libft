/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tag_rule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:46:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/03 20:32:27 by aait-ihi         ###   ########.fr       */
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

t_list *valid_cam_light(t_list *nodes, t_tag_rule *rules)
{
    t_tag_rule *rule;
    int i;

    i = 0;
    rule = find_hash_table("camera");
    if (!valide_rule(nodes->content, rule))
        return (0);
    rule = find_hash_table("light");
    while (nodes)
    {
        if(!ft_strequ(((t_xml_tag *)nodes->content)->name, "light"))
            break;
        if (!valide_rule(nodes->content, rule))
            return (0);
        node = nodes->next;
        i++;
    }
    if(i == 0);
        return(ft_printf("except light found\n") * 0);
    return(nodes);
}

bool valide_tags(t_xml_tag *root, t_tag_rule *rules)
{
    t_list *node;
    t_xml_tag tmp;
    t_tag_rule *rule;

    if (!ft_strequ(root->name, "RT"))
    {
        ft_printf("root element not valid");
        return (0);
    }
    if (!(node = valid_cam_light(root->nodes, rules)))
        return (ft_printf("No object found\n") * 0);
    while (node)
    {
        if (!(rule = find_hash_table(((t_xml_tag *)node->content)->name)))
            return (ft_printf("invalid tag name") * 0);
        if (!valide_rule(node->content, rule))
            return (0);
        node = node->next;
    }
    return (1);
}