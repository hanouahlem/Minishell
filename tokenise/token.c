/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:32:30 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/14 20:40:16 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_token(char *str, int *index_l, t_token **tokenis)
{
	t_token	*node_t;

	str[*index_l] = '\0';
	node_t = ft_lstnew_tok(str);
	ft_lstadd_back_tok(tokenis, node_t);
	*index_l = 0;
}

void	process_special_char(char *line, char *str, int *i, t_token **tokenis)
{
	t_token	*node_t;

	str[0] = line[*i];
	if (line[(*i) + 1] == '>' || line[(*i) + 1] == '<')
	{
		*i += 1;
		str[1] = line[*i];
		str[2] = '\0';
	}
	else
		str[1] = '\0';
	node_t = ft_lstnew_tok(str);
	ft_lstadd_back_tok(tokenis, node_t);
}

void	split_line(int i, char *line, t_token **tokenis)
{
	int		index_l;
	char	*str;

	index_l = 0;
	str = ft_strdup(line);
	while (line[++i])
	{
		if (line[i] == ' ')
		{
			if (index_l > 0)
				handle_token(str, &index_l, tokenis);
		}
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			if (index_l > 0)
				handle_token(str, &index_l, tokenis);
			process_special_char(line, str, &i, tokenis);
		}
		else
			str[index_l++] = (line[i] ^ (line[i] >> 31)) - (line[i] >> 31);
	}
	if (index_l > 0)
		handle_token(str, &index_l, tokenis);
	*tokenis = add_prev(*tokenis);
	free(str);
}

/*

                        mmmmm ,,                    ,,                        
          mm            MM    db                  `7MM                        
          MM            MM                          MM                        
,pP"Ybd mmMMmm `7Mb,od8 MM  `7MM  `7MMpMMMb.   ,M""bMM  .gP"Ya `7M'   `MF'    
8I   `"   MM     MM' "' MM    MM    MM    MM ,AP    MM ,M'   Yb  `VA ,V'      
`YMMMa.   MM     MM     MM    MM    MM    MM 8MI    MM 8M""""""    XMX        
L.   I8   MM     MM     MM    MM    MM    MM `Mb    MM YM.    ,  ,V' VA.      
M9mmmP'   `Mbmo.JMML.   MM  .JMML..JMML  JMML.`Wbmd"MML.`Mbmmd'.AM.   .MA.    
                        MM                                                    
                        MMmmm                                          mmmmmmm
                                                                              
  ,,                  mmmmm                                                   
`7MM                     MM                                                   
  MM                     MM                                                   
  MM     M         M     MM                                                   
  MM     M         M     MM     mmmmmmmmm                                     
  MM mmmmMmmmm mmmmMmmmm MM                                                   
  MM     M         M     MM     mmmmmmmmm                                     
.JMML.   M         M     MM                                                   
                         MM                                                   
                      mmmMM                                                   
                                                                              
    .. .. ,,    ,,                      mmmmm ,, mmmmm                        
  pd'pd'`7MM    db                      MM    db    MM                        
 6P 6P    MM                            MM          MM     `\\.               
6M'6M'    MM  `7MM  `7MMpMMMb.  .gP"Ya  MM  `7MM    MM        `\\:.           
MN MN     MM    MM    MM    MM ,M'   Yb MM    MM    MM           `\\.         
MN MN     MM    MM    MM    MM 8M"""""" MM    MM    MM          ,;//'         
YM.YM.    MM    MM    MM    MM YM.    , MM    MM    MM       ,;//'            
 Mb Mb  .JMML..JMML..JMML  JMML.`Mbmmd' MM  .JMML.  MM     ,//'               
  Yq.Yq.                                MM          MM                        
    `` ``                               MMmmm    mmmMM                        
                                                                              
        ..                                                                    
         `bq        ,gM""bg      ,gM""bg                                      
           YA       8MI  ,8      8MI  ,8                                      
 ,pP""Yq.  `Mb       WMp,"        WMp,"                                       
6W'    `Wb  8M      ,gPMN.  jM"' ,gPMN.  jM"'                                 
8M      M8  8M     ,M.  YMp.M'  ,M.  YMp.M'                                   
YA.    ,A9 ,M9     8Mp   ,MMp   8Mp   ,MMp                                    
 `Ybmmd9'  dM      `YMbmm'``MMm.`YMbmm'``MMm.                                 
         .pY                                                                  
        ''                                                                    
                                                                              
  ,,    ,,                      mmmmm ,, mmmmm ..         MM MM               
`7MM    db                      MM    db    MM  `bq       MM MM               
  MM                            MM          MM    YA      MM MM               
  MM  `7MM  `7MMpMMMb.  .gP"Ya  MM  `7MM    MM    `Mb     MM MM               
  MM    MM    MM    MM ,M'   Yb MM    MM    MM     8M     MM MM               
  MM    MM    MM    MM 8M"""""" MM    MM    MM     8M     MM MM               
  MM    MM    MM    MM YM.    , MM    MM    MM    ,M9     MM MM               
.JMML..JMML..JMML  JMML.`Mbmmd' MM  .JMML.  MM    dM      MM MM               
                                MM          MM  .pY       MM MM               
                                MMmmm    mmmMM ''         MM MM               
                                                                              
      ,,    ,,                      mmmmm ,, mmmmm                            
    `7MM    db                      MM    db    MM                            
      MM                            MM          MM                            
      MM  `7MM  `7MMpMMMb.  .gP"Ya  MM  `7MM    MM      gp                    
      MM    MM    MM    MM ,M'   Yb MM    MM    MM      ""                    
mmmmm MM    MM    MM    MM 8M"""""" MM    MM    MM                            
      MM    MM    MM    MM YM.    , MM    MM    MM      ,,                    
    .JMML..JMML..JMML  JMML.`Mbmmd' MM  .JMML.  MM      dg                    
                                    MM          MM      ,j                    
                                    MMmmm    mmmMM     ,'                     

*/