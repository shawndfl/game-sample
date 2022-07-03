import React, {useEffect, useState} from 'react';

function UserRequest() {

    useEffect(() => {
        console.debug("Requesting from /api/user");
        const api = "/api/user"
        fetch(api).then((response) => {
            return response.json();
        }).then((data) => {
            console.log(data);
            setLoading(false);
        });
    }, []);

    const [loading, setLoading] = useState(true);

    return (
        <>
            <div> {
                loading === true ? (
                    <div>
                        Loading...</div>
                ) : (
                    <div>Got it</div>
                )
            } </div>
        </>
    );
}

export default UserRequest;
