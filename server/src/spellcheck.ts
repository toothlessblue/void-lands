import SpellChecker from 'spellchecker';

process.env.LANG = 'en_US'; // hunspell dict doesn't work without this

export function isMisspelled(word: string) {
    return SpellChecker.isMisspelled(word.toLocaleUpperCase());
}