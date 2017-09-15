type HTML = [HTML_element]

data HTML_element
    = HTML_text String
    | HTML_font Font_tag HTML
    | HTML_p HTML
    | HTML_ul [HTML]
    | HTML_ol [HTML]

data Font_tag = Font_tag (Maybe Int)
                         (Maybe String)
                         (Maybe Font_color)

data Font_color
    = Colour_name String
    | Hex Int
    | RGB Int Int Int


