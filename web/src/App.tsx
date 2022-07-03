import './App.css';
import Header from './container/header/Header'
import Home from './container/home/Home'
import {BrowserRouter, Routes, Route} from "react-router-dom";
import UserRequest from "./api/UserRequest";
import { ThemeProvider, createTheme } from '@mui/material/styles';
import Footer from "container/footer/Footer"
import { Box } from '@mui/material';

function App() {    

    const theme = createTheme({
        palette: {
            primary: {
                main: "#bdbdbd"

            },
            secondary: {
                main: "#9e9d24"                
            }, 
            text: {
                primary: "#212121",
                secondary: "#000000"
            }           
        }
    });

    return (
        <ThemeProvider theme={theme}>
            <Box sx={{
                backgroundColor: (theme) => theme.palette.primary.light 
            }}>                
                <Header/>                
                <BrowserRouter>
                    <Routes>
                        <Route path={process.env.PUBLIC_URL + "/"}
                            element={<Home/>}></Route>
                        <Route path={process.env.PUBLIC_URL + "/data"}
                            element={<UserRequest/>}></Route>
                    </Routes>
                </BrowserRouter>
                <Footer/>
            </Box>
        </ThemeProvider>
    );
}

export default App;
