/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:16:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/03 20:35:13 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xml.h"

int valid_vec(t_xml_tag *tag)
{
    const *char tab[] = {"x", "y", "z", NULL};
    t_list *nodes;
    t_xml_tag *tmp;
    int i;

    nodes = tag->nodes;
    while (nodes)
    {
        if (i == 3)
            return (ft_printf("additional tag here\n") * 0);
        tmp = nodes->content;
        if (!ft_strequ(tab[i], tmp->name))
            return (ft_printf("invalid tag name ") * 0);
        if (!ft_number(tmp->value))
            return (ft_printf("invalide values\n") * 0);
        nodes = nodes->next;
        i++;
    }
    return (1);
}

int valid_enum(t_xml_tag *tag, const char *enums)
{
    char **tab;
    bool is_in_arr;

    tab = ft_strsplit(enums);
    is_in_arr = ft_str_in_arr(tab, tag->value));
    ft_free_2d_tab(tab);
    if (!is_in_arr)
        ft_printf("invalid value\n");
    return (is_in_arr);
}

bool valid_cut_exist(t_xml_tag *tag)
{
    t_list *nodes;
    t_xml_tag *tmp;
    int i;

    nodes = tag->nodes;
    while (nodes)
    {
        if (i == 2)
            return (ft_printf("additional tag here\n") * 0);
        tmp = nodes->content;
        if (!ft_strequ("limit_xyz", tmp->name))
            return (ft_printf("invalid tag name ") * 0);
        if (!valid_vec(tmp))
            return (0);
        nodes = nodes->next;
        i++;
    }
    return (1);
}

bool valid_rule_by_type(t_xml_tag *tag, char *type, char *dep)
{
    if (ft_strequ("vec", type))
        return (valid_vec(tag));
    if (ft_strequ("enum", type))
        return (valid_enum(tag, dep));
    if (ft_strequ("cut_exist", type))
        return (valid_cut_exist(tag));
    if (ft_strequ("double", type))
    {
        if (!is_nbr(tag->value))
            return (ft_printf("invalid value\n") * 0);
        return (1);
    }
    if (ft_strequ("uint", type))
    {
        if (!is_nbr(tag->value))
            return (ft_printf("invalid value\n") * 0);
        return (1);
    }
    return (0);
}

bool valide_rule(t_xml_tag *tag, t_rule_tag *rules)
{
    t_list *node;
    int i;

    i = 0;
    if (!ft_strequ(tag->name, rule->name))
    {
        ft_printf("exepted tag%s found %s \n");
        return (0);
    }
    node = tag->nodes;
    while (rules[i])
    {
        if (node == NULL)
        {
            ft_printf("tag %s not found", rules[i].name);
            return (0);
        }
        if (!valid_rule_by_type(node->content, rule->type, rules[i].dependency))
            return (0);
        i++;
        node = node->next;
    }
}

bool valide_tags(t_xml_tag *root, t_tag_rule *rules)
{
    t_list *node;
    int i;

    i = 0;
    if (!ft_strequ(root->name, "RT"))
    {
        ft_printf("root element not valid");
        return (0);
    }
    node = root->nodes;
    while (nodes)
    {
        if (node == NULL)
        {
            ft_printf("tag %s not found", rules[i].name);
            return (0);
        }
        if (!valide_rule(node->content, rules[i].rule_tags))
            return (0);
        i++;
        node = node->next;
    }
    if (node)
        return (ft_printf("additional tag here\n") * 0);
    return (1);
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