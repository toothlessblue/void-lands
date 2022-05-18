import * as path from 'path';

export default {
    fsRoot: path.join(__dirname, '../../').slice(0, -1),
    environment: (() => {
        const env = process.env.NODE_ENV;
        if (env !== 'dev' && env !== 'live') {
            console.error('NODE_ENV unrecognised, please provide "dev" or "live" with environment vars.');
            process.exit(1);
        }
        if (env === 'dev') {
            console.warn('Running in dev mode');
        }
        return env;
    })(),
};
