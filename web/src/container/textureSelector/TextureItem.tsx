
import { ThreeMp } from "@mui/icons-material";
import { Button, Paper } from "@mui/material"

export default function TextureItem() {
    
    const click = ( ) => {
        
    }
    return <Paper elevation={2}
        sx= {{
            height : 200,
            m: 2,
     backgroundColor: (theme) =>
        theme.palette.secondary.light
     
    }}> 
    <Button color='inherit' variant="contained" sx={ { borderRadius: 28 } } onClick={click}>Add texture</Button>
    </Paper>;
}