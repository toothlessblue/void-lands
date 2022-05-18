import {TwingEnvironment, TwingFilter, TwingFunction, TwingLoaderFilesystem, TwingMarkup} from 'twing';
import {Request} from 'express';
import * as fs from 'fs';
import {minify, Options} from 'html-minifier';

const twingLoader = new TwingLoaderFilesystem('./server/templates');
const twing = new TwingEnvironment(twingLoader);

function timeSince(since: Date) {
    const difference = Math.floor((Date.now() - since.getTime()) / 1000);

    if (difference > 31556952) { // Year
        const count = Math.floor(difference / 31556952);
        return {
            suffix: 'year' + (count === 1 ? '' : 's'),
            count: count
        };
    }

    if (difference > 2629746) { // Month
        const count = Math.floor(difference / 2629746);
        return {
            suffix: 'month' + (count === 1 ? '' : 's'),
            count: count
        };
    }

    if (difference > 72000) { // Day
        const count = Math.floor(difference / 72000);
        return {
            suffix: 'day' + (count === 1 ? '' : 's'),
            count: count
        };
    }

    if (difference > 3600) { // Hour
        const count = Math.floor(difference / 3600);
        return {
            suffix: 'hour' + (count === 1 ? '' : 's'),
            count: count
        };
    }

    if (difference > 60) { // Minutes
        const count = Math.floor(difference / 60);
        return {
            suffix: 'minute' + (count === 1 ? '' : 's'),
            count: count
        };
    }

    return {
        suffix: 'second' + (difference === 1 ? '' : 's'),
        count: difference
    };
    // Seconds
}

const timeSinceFilter = new TwingFilter('time_since', async (value: string) => {
    const time = timeSince(new Date(value));
    return `${time.count} ${time.suffix}`;
}, []);

const blogLinkFilter = new TwingFunction('link_to_blog', async (linkText: string, blogSlug: string) => {
    return new TwingMarkup(`<a href="/blogs/${blogSlug}" class="inline-link">${linkText}</a>`, 'UTF-8');
}, []);

const renderRawHtmlFile = new TwingFunction('render_raw_file', async (filepath: string) => {
    return new TwingMarkup(fs.readFileSync(filepath).toString(), 'UTF-8');
}, []);

twing.addFilter(timeSinceFilter);
twing.addFunction(renderRawHtmlFile);
twing.addFunction(blogLinkFilter);

const htmlMinifierOptions: Options = {
    caseSensitive: true,
    minifyJS: true,
    minifyCSS: true,
    removeComments: true,
    removeEmptyAttributes: true,
    collapseWhitespace: true,
};

function minifyHTML(html: string): string {
    return minify(html, htmlMinifierOptions);
}

export async function render(req: Request, twigTemplate: string, properties: Record<string, unknown> = {}): Promise<string> {
    return minifyHTML(await twing.render(twigTemplate, {
        req: req,
        ...properties,
    }));
}